# ofxGrowth

![Branches](examples/branches.jpg?raw=true)

Openframeworks addon for exploring procedural growth patterns.

Based primarily on hand-drawn processes, exploring plant growth. This addon is meant to be
abstracted enough that it can be used for naiive simulations of capillary action, plant growth,
ant-hill structures, etc, and the language used will be tweaked to match that purpose.

---

## Sequence

1. Draw a line from a starting point, to a destination point. The destination point is constrained to a certain degree to the direction and magnitude of the vector before it.
  * *repeat n times, until a branch is created*
2. Loop through the points of all branches, and at semi-random points, generate new branches
  * *repeat n levels deep*
  * For each new branch, create a corresponding mesh for display.
3. Loop through all created branches
  * Apply coloring

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
* ~~**Leaf Width**~~
  * ~~*How wide is the leaf?*~~
  * ~~*What is the angle between the two sides of a leaf?*~~
* ~~**Leaf Level**~~
  * ~~*At what point do we begin seeing leaves?*~~

---

## Methods

The core generative methods are:

```
void setupBranches();
ofMesh generateBranch(ofVec3f origin, ofVec3f initial_vector, int level);
```

The structure underlying all of this is the vector that organizes the branches. The format it takes is:

```
vector< vector<ofMesh> > branches;
```

## setupBranches()

setupBranches() is currently being used to control the overall recursion of the sequence. Within this method, the core branch is generated, and then generateBranch() is called to recursively, for each level of depth, and also for each node within each branch.

Description of the main recursion:

```
create initial, core branch

for each level of depth (current_level)
  for each branch in the current_level (current_branch)
    for each node in the current_branch (current_node)
      if the current_level isn't the maximum level (since we are adding new branches for each level, stop)
        add a branch to the temporary vector<ofMesh>, if probability allows
  push back the entire level of branches (creating current_level + 1)
```

## generateBranch()

generateBranch() controls the actual construction of the branch, and contains a bulk of the
actual logic. The method returns an ofMesh object, to be added to the branches vector.

```
create a temporary branch to manipulate

add a point to the location of the node we are building off of (origin)

calculate diminished segment count, and diminished length

for each segment
  calculate a random point, loosely aligned with the previous growth vector with a random length, constrained by
  the diminished length value

  add vertex to the temporary branch mesh

  update growth vector for next iteration

method returns the temporary branch
```

## generateLeaf() (remove)

Currently there is a method for leaf generation, but this isn't entirely necessary for the functioning of a more
abstracted growth generation class. This needs to be moved.
