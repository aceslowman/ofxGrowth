#include "ofxGrowth.h"


//--------------------------------------------------------------
ofxGrowth::ofxGrowth(){
    this->density       = 0.2;
    this->length        = 0.7;
    this->scale         = 60;
    this->segments      = 35;
    this->depth         = 3;
    this->leaf_level    = 3;
    this->crookedness   = 0.5;
    this->origin        = ofVec3f(0,0,0);
    this->f_dim         = 0.5;
    this->color_mode    = 1;
    this->growth_vector = ofVec3f(0,1,0);
    this->dim_strokewidth = false;

    glPointSize(8);
}

//--------------------------------------------------------------
void ofxGrowth::setup(){
    this->node_size = 0;

    setupBranches();
//    updateNodeSize();
    colorMesh(this->color_mode);
}

//--------------------------------------------------------------
void ofxGrowth::colorMesh(int coloring_type){
    switch (coloring_type) {
        case 0: //color for each branch
            
            for(int i = 0; i < branches.size(); i++){
                for(int j = 0; j < branches[i].size(); j++){
                    ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                    
                    branches[i][j].addColors(&branch_color, branches[i][j].getVertices().size());
                    for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                        branches[i][j].setColor(k, branch_color);
                    }
                }
            }
            
            for(int i = 0; i < leaves.size(); i++){
                for(int j = 0; j < leaves[i].size(); j++){
                    ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                    leaves[i][j].setFillColor(branch_color);
                }
            }
            
            break;
            
        case 1: //color for each level
            for(int i = 0; i < branches.size(); i++){
                ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                
                for(int j = 0; j < branches[i].size(); j++){
                    branches[i][j].addColors(&branch_color, branches[i][j].getVertices().size());
                    for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                        branches[i][j].setColor(k, branch_color);
                    }
                }
            }
            
            for(int i = 0; i < leaves.size(); i++){
                ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                for(int j = 0; j < leaves[i].size(); j++){
                    
                    leaves[i][j].setFillColor(branch_color);
                }
            }
            
            break;
            
        case 2: //all black branches, random colored leaves
            for(int i = 0; i < branches.size(); i++){
                
                if(i < this->leaf_level){
                    for(int j = 0; j < branches[i].size(); j++){
                        for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                            branches[i][j].setColor(k, ofFloatColor(0));
                        }
                    }
                }else{
                    ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());

                    for(int j = 0; j < branches[i].size(); j++){
                        for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                            branches[i][j].setColor(k, branch_color);
                        }
                    }
                }
            }
            
            for(int i = 0; i < leaves.size(); i++){
                ofFloatColor branch_color = ofFloatColor(ofRandomuf(),ofRandomuf(),ofRandomuf());
                
                for(int j = 0; j < leaves[i].size(); j++){
                    
                    leaves[i][j].setFillColor(branch_color);
                }
            }
            
            break;
        case 3: //All branches black, with no opacity. Empty.
            
            for(int i = 0; i < branches.size(); i++){
                for(int j = 0; j < branches[i].size(); j++){
                    for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                        branches[i][j].setColor(k, ofColor(0,0,0,0));
                    }
                }
            }
            
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofxGrowth::setupBranches(){
    vector<ofMesh> t_branches;
    
    ofVec3f initial_vector = this->growth_vector;
    
    ofMesh t_branch = generateBranch(this->origin, initial_vector, 0);
    t_branches.push_back(t_branch);
    branches.push_back(t_branches);
    
    for(int current_level = 0; current_level <= this->depth; current_level++){
        vector<ofMesh> t_branches;
        vector<ofPath> t_leaves;
        
        for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){
            
            /*
             this really just amounts to a hack, I should still ask about this
             essentially this is designed to create new branches based on the 
             recursion through the previous level. So the last level ends up being
             inaccessible.
             */
            
            if(current_level != this->depth){
                for(int current_node = 0; current_node < branches[current_level][current_branch].getVertices().size(); current_node++){
                    
                    ofVec3f current_node_position = branches[current_level][current_branch].getVertex(current_node);
                    ofVec3f t_vec = initial_vector.rotate(ofRandomf()*360, initial_vector);
                    
                    if(ofRandomuf() < this->density){
                        ofMesh t_branch = generateBranch(current_node_position, t_vec, current_level+1);
                        t_branches.push_back(t_branch);
                    }
                }
            }
            
            if(current_level >= this->leaf_level){
                ofPath t_leaf = generateLeaf(branches[current_level][current_branch].getVertices(),current_level+1);
                t_leaves.push_back(t_leaf);
            }
        }
        branches.push_back(t_branches);
        leaves.push_back(t_leaves);
    }
}

//--------------------------------------------------------------
ofMesh ofxGrowth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
    ofMesh t_branch;
    t_branch.setMode(OF_PRIMITIVE_LINE_STRIP);
    t_branch.setupIndicesAuto();
    
    t_branch.addIndex(0);
    t_branch.addVertex(origin);
    
    //Diminish parameters
    int t_segments = this->segments;
    float t_length = (this->length * this->scale) * pow(this->f_dim,level);
    
    //Initialize vector and point
    ofVec3f t_vec          = initial_vector;
    ofVec3f t_point        = origin;
    ofVec3f t_point_mirror = origin;
    
    //begin assembling one cycle of sequence
    for(int i = 1; i < t_segments; i++){
        float t_length_rand = ( t_length * ofRandomuf() );
        t_point = t_point + (t_vec *  t_length_rand);
        
        t_branch.addIndex(i);
        t_branch.addColor(ofFloatColor(0));
        t_branch.addVertex(t_point);
        
        t_vec = ofVec3f(
            ofClamp(t_vec.x + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.y + (ofRandomf() * this->crookedness),-1.0,1.0),
            ofClamp(t_vec.z + (ofRandomf() * this->crookedness),-1.0,1.0)
        );
        
        this->node_size++;
    }
    
    return t_branch;
}

//--------------------------------------------------------------
ofPath ofxGrowth::generateLeaf(ofPolyline poly, int level){
    ofMesh t_leaf;
    ofPath t_path, t_path_mirrored;
    
    t_path.moveTo(poly[0]);
    t_path_mirrored.moveTo(poly[0]);
    
    for(int i = 0; i < poly.size() - 1; i++){
        ofVec3f p1(poly[i]);
        ofVec3f p2(poly[i + 1]);

        ofVec3f t_vec(p2 - p1);
        ofVec3f t_vec_ortho(ofRandomf(),ofRandomf(),ofRandomf());
        t_vec_ortho.cross(t_vec.normalize());
        
        ofVec3f cp1(p1 - (t_vec_ortho*15));
        ofVec3f cp2(p2 - (t_vec_ortho*15));
        ofVec3f cp3(p1 + (t_vec_ortho*15));
        ofVec3f cp4(p2 + (t_vec_ortho*15));

        t_path.bezierTo(cp1,cp2,p2);
        t_path_mirrored.bezierTo(cp3,cp4,p2);
    }
    
    t_path.append(t_path_mirrored);
    t_path.close();
    
    return t_path;
}

//--------------------------------------------------------------
void ofxGrowth::drawPoints(){
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            branches[i][j].setMode(OF_PRIMITIVE_POINTS);
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawMeshes(){
    for(int i = 0; i < branches.size(); i++){
        int t_width = 2;
        
        if(this->dim_strokewidth)
            t_width = (10) * pow(this->f_dim,i);
            
        for(int j = 0; j < branches[i].size(); j++){
            glLineWidth(t_width);
            
            branches[i][j].setMode(OF_PRIMITIVE_LINE_STRIP);
            branches[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawLeaves(){
    for(int i = this->leaf_level; i < leaves.size(); i++){
        for(int j = 0; j < leaves[i].size(); j++){
            leaves[i][j].setFilled(true);
            leaves[i][j].draw();
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::drawDebug(){
    for(int i = 0; i < branches.size(); i++){
        for(int j = 0; j < branches[i].size(); j++){
            for(int k = 0; k < branches[i][j].getVertices().size(); k++){
                ofPushMatrix();
                ofTranslate(branches[i][j].getVertices()[k]);
                int t_ind = branches[i][j].getIndices()[k];
                ofDrawBitmapString("ID:"+ofToString(t_ind)+" L:"+ofToString(i),0,0);
                ofPopMatrix();
            }
        }
    }
}

//--------------------------------------------------------------
void ofxGrowth::clearAll(){
    branches.clear();
    leaves.clear();
}

////--------------------------------------------------------------
//void ofxGrowth::updateNodeSize(){
//    this->node_size = 0;
//    
//    for(int current_level = 0; current_level < branches.size(); current_level++){
//        for(int current_branch = 0; current_branch < branches[current_level].size(); current_branch++){
//            for(int current_node = 0; branches[current_level][current_branch].getVertices().size(); current_node++){
//                this->node_size++;
//            }
//        }
//        
//    }
//    
//}

void ofxGrowth::setDensity(float density){this->density = density;}
void ofxGrowth::setLength(float length){this->length = length;}
void ofxGrowth::setScale(float scale){this->scale = scale;}
void ofxGrowth::setSegments(int segments){this->segments = segments;}
void ofxGrowth::setDepth(int depth){this->depth = depth;}
void ofxGrowth::setLeafLevel(int leaf_level){this->leaf_level = leaf_level;}
void ofxGrowth::setCrookedness(float crookedness){this->crookedness = crookedness;}
void ofxGrowth::setColormode(int color_mode){this->color_mode = color_mode;colorMesh(color_mode);}

int ofxGrowth::getNodeSize(){ return this->node_size; }
