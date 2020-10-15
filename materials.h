// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

// PLASTIC MATERIALS FOR THE CUBE
static materialStruct whitePlasticMaterials = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.55, 0.55, 0.55, 1.0},
  { 0.7, 0.7, 0.7, 1.0},
  32.0
};
static materialStruct greenPlasticMaterials = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.1, 0.35, 0.1, 1.0},
  { 0.45, 0.55, 0.45, 1.0},
  32.0
};
static materialStruct redPlasticMaterials = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.5, 0.0, 0.0, 1.0},
  { 0.7, 0.6, 0.6, 1.0},
  32.0
};
static materialStruct cyanPlasticMaterials = {
  { 0.0, 0.1, 0.06, 1.0},
  { 0.0, 0.50980392, 0.50980392, 1.0},
  { 0.50196078, 0.50196078, 0.50196078, 1.0 },
  32.0
};
static materialStruct yellowPlasticMaterials = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.5, 0.5, 0.0, 1.0},
  { 0.6, 0.6, 0.5, 1.0},
  32.0
};
static materialStruct orangeMaterials = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.5, 0.25, 0.0, 1.0},
  { 0.5, 0.5, 0.5, 1.0},
  32.0
};

// MATERIAL FOR THE EDGES OF THE CUBE. AND THE INSIDE BITS
static materialStruct blackPlasticMaterials = {
  { 0., 0. , 0., 1.0f },
  { 0., 0., 0., 1.0f },
  { 1., 1., 1., 1.0f },
  128
};




// ALTERNATIVE MATERIALS THAT ARE SHINIER
static materialStruct obsidianMaterials = {
  { 0.05375f, 0.05f, 0.06625f, 0.82f},
  { 0.18275f, 0.17f, 0.22525f, 0.82f},
  { 0.332741f, 0.328634f, 0.346435f, 0.82f },
  32.0
};
static materialStruct emeraldMaterials = {
  {0.0215, 0.1745, 0.0215, 1.0},
  {0.07568, 0.61424, 0.07568, 1.0},
  {0.633, 0.727811, 0.633, 1.0},
  77.0
};
static materialStruct rubyMaterials = {
  { 0.1745, 0.01175, 0.01175, 1.0},
  { .61424, 0.04136, 0.04126, 1.0},
  { 0.727811, 0.626959, 0.6269, 1.0},
  77.0
};
static materialStruct jadeMaterials = {
  { 0.135, 0.2225, 0.8, 1.0},
  { 0.54, 0.89, 0.63, 1.0},
  { 0.316228, 0.316228, 0.8, 1.0},
  128.0
};
static materialStruct orangeGoldMaterials = {
  { 0.8, 0.4, 0.0, 1.0},
  { 0.8, 0.4, 0.0, 1.0},
  { 0.9, 0.5, 0.5, 1.0},
  128.0
};
static materialStruct goldMaterials = {
  { 0.6, 0.6, 0.06, 1.0},
  { 0.55, 0.51, 0.09, 1.0},
  { 0.8, 0.8, 0.2, 1.0},
  128.0
};
static materialStruct pearlMaterials = {
  { 0.25, 0.20725, 0.20725, 1.0},
  { 1.0, 0.829, 0.829, 1.0},
  { 0.296648, 0.296648, 0.296648, 1.0},

};
