# beginners-growth
Procedural plant experiments

Before I begin exploring L-Systems, I want to see if I can mimic plant growth similar to what I might draw by hand.

---

## Sequence

1. Draw a line from a starting point, to a destination point. The destination point is constrained to a certain degree to the direction and magnitude of the vector before it.
  * *repeat n times, until a branch is created*
2. Loop through the points of all branches, and at semi-random points, generate new branches
  * *repeat n levels deep*
  * For each new branch, create a corresponding mesh for display.
3. Loop through all created branches
  * Apply coloring
  * Change drawing mode to TRIANGLE_FAN for all branches belonging to levels above the LEAF_LEVEL

---

## Parameters

* **Density**
  * *What is the probability of a new branch being drawn off of a particular node?*
* **Length**
  * *What is the maximum length of a segment?*
* **Segments**
  * *How many bends does the branch have?*
* **Depth (levels)**
  * *How deep does the recursion go?*
* **Crookedness**
  * *How constrained are the points on the branch to a particular vector?*
* **Leaf Width**
  * *How wide is the leaf?*
  * *What is the theta between the two sides of a leaf?*
* **Leaf Level**
  * *At what point do we begin seeing leaves?*
---

## Methods

This is something I need to put a lot of thought into.

I need to be able to just create a branch, in the main.cpp file. All I pass to that branch is it's parameters, or just the ones necessary.

```
  setup();
  update();
  draw();
```  

Within setup, I need to set all of my defaults. All of these should be normalized, 0 - 1. With that said, a few of these have no maximum, so some sort of limit will need to be implemented, particularly segments and depth.

```
void Growth::setup(){
  this->density      = ofRandomuf();
  this->length       = ofRandomuf();
  this->segments     = ofRandom(10);
  this->depth        = ofRandom(10);
  this->leaf_level   = ofRandom(10);
  this->straightness = ofRandomuf();
}
```

I also want to make sure that the method between leaves and branches stay as similar as possible. All will use an ofMesh class.

This also brings me to the issue of leaves. It seems important to have some separate handling of leaves, but most of the methods will be the same. *Maybe* this means that I shouldn't extend ofMesh, instead have the Growth class own ofMesh objects.

* There is a branch
* The branch has leaves
* LATER: A tree has branches, each of which have leaves.

```
class Growth : public ofMesh {

  public:

    void setup();
    void update();
    void draw();

    void generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
    void setupBranch();

    float density;
    float length;
    int   segments;
    int   depth;
    int   leaf_level;
    float straightness;

    float f_dim; //diminishment factor, size of growth in subsequent levels

    ofMesh branch;
    vector<ofMesh> leaves;
}
```

Essentially, I think if we go beyond a certain number of levels (leaf_level), then we will switch to placing this mesh within a vector, instead of appending it onto the preexisting branch.

## generateBranch()

The generateBranch() method is going to do the bulk of the actual construction. For generateBranch() to work, we need to know a few things.

1. Where did the growth start? The root? The node on a branch before it?
2. What is the initial vector? Which direction was this growth pointing?
3. What level of recursion are we at?

I then need to get a few pieces of information for this specific iteration. Every level deeper we go, some things change.

* Branches become shorter, and consist of less segments. (t_length, t_segments)

These will be dictated by some sort of factor affecting how fast subsequent branches shrink in size.

The factor is f_dim, I want it to be -1 - 1, with the maximum being some hardcoded limit in small or large sizes.

This is going to be implemented with `pow(f_dim,level)`

```
//Diminish parameters
int t_segments = this->segments * pow(f_dim,level);
float t_length = this->length   * pow(f_dim,level);
```

Now, to actually work through the cycle, I need to calculate the point for step 1. t_point is the vector, times the length (which is random, with t_length as the maximum), plus the previous t_point.

```
t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );
```

After everything else is calculated, at the end of the loop I need to prepare the new semi-random vector. The vector is the previous vector, plus a random direction, -1 to 1, diminished by a degree of smoothness.

```
t_vec = ofVec3f(
  ofClamp(t_vec.x + (ofRandomf() * straightness),0.0,1.0),
  ofClamp(t_vec.y + (ofRandomf() * straightness),0.0,1.0),
  ofClamp(t_vec.z + (ofRandomf() * straightness),0.0,1.0)
);
```

```
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofPath t_path;

    this->moveTo(origin);

    //Diminish parameters
    int t_segments = this->segments * pow(f_dim,level);
    float t_length = this->length   * pow(f_dim,level);

    //Initialize vector and point
    ofVec3f t_vec = initial_vector;
    ofVec3f t_point = origin;

    //begin assembling one cycle of sequence
    for(int i = 0; i < t_segments; i++){

        t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );

        this->lineTo(t_point);

        t_vec = ofVec3f(
                        ofClamp(t_vec.x + (ofRandomf() * straightness),0.0,1.0),
                        ofClamp(t_vec.y + (ofRandomf() * straightness),0.0,1.0),
                        ofClamp(t_vec.z + (ofRandomf() * straightness),0.0,1.0)
                        );
    }

    this->newSubPath();
}
```

## setupBranch()

I need some kind of controller for the recursion. Maybe there is a more efficient method that I could use to get some sort of self-contained function for generateBranch, but setupBranch() will work as that for now.

setupBranch() will call to generateBranch, within loops. Essentially, loop through every existing branch, and use probability to choose which branches will beget new branches.

First, begin looping through the first level.
Then, loop through every node in that branch.
If the odds are that the current node is selected, generate a new branch.

How do I target individual branches, in the same way I did for ofPath?

```
void Growth::setupBranch(){

    ofVec3f initial_vector = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());

    generateBranch(this->origin, initial_vector, 0);

    int current_branch = 1;
    int current_level  = 1;

    for(int i = 0; i <= this->depth; i++){

        for(int j = 0; j < current_branch; j++){

            for(int k = 0; k < this->getOutline()[i].size(); k++){
                ofVec3f current_node_position = this->getOutline()[i].getPointAtIndexInterpolated(k);
                ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);

                if(ofRandomuf() < this->density){
                    generateBranch(current_node_position, t_vec, current_level);
                }
            }
            current_branch++;
        }
        current_level++;
    }
}
```

## The issue with ofMesh creation, instead of ofPath

I am starting to question creating the mesh throughout the process. I think that this might be a misunderstanding of the purpose of ofPath and ofMesh individually, but if I was to use ofPath, with meticulously managed indices and hierarchies, THEN, create a seperate set of methods to handle meshing the paths, with it's own level logic and attention to depth.

I think this actually might be better, now that I'm seeing that the use of ofMesh won't really allow me to say, loop through all individual branches seperately. There just wouldn't be the logic present in the mesh. Rewriting the generateBranch section, then the setupBranch section.
---

  ![Screenshot](../images/basic-sequence.png?raw=true)
