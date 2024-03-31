/*  by Alun Evans 2016 LaSalle (aevanss@salleurl.edu) */

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//include some standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "imageloader.h"

//include OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

//include some custom code files
#include "glfunctions.h" //include all OpenGL stuff
#include "Shader.h" // class to compile shaders

#include <string>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;
using namespace glm;

string basepath = "assets/";

//univers
string inputfile3 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes3;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials3;

//Sol
string inputfile = basepath + "sphere.obj";   
vector< tinyobj::shape_t > shapes;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials;

//Mercuri
string inputfile2 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes2;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials2;

//Venus
string inputfile4 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes4;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials4;

//Terra
string inputfile5 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes5;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials5;

//Lluna
string inputfile6 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes6;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials6;

//Mart
string inputfile7 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes7;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials7;

//Jupiter
string inputfile8 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes8;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials8;

//Saturn
string inputfile9 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes9;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials9;

//Anells Saturn
string inputfile44 = basepath + "plane.obj";
vector< tinyobj::shape_t > shapes44;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials44;

//Urà
string inputfile10 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes10;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials10;

//Neptú
string inputfile11 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes11;    // the vector that will hold the mesh data
vector< tinyobj::material_t > materials11;

//global variables to help us do things
int g_ViewportWidth = 712; int g_ViewportHeight = 712; // Default window size, in pixels
double mouse_x, mouse_y; //variables storing mouse position
const vec3 g_backgroundColor(0.2f, 0.2f, 0.2f); // background colour - a GLM 3-component vector

GLuint g_simpleShader = 0; //shader identifier
GLuint g_simpleShader_sky = 0;
GLuint g_simpleShader_rings = 0;

GLuint g_Vao = 0; //vao
GLuint g_NumTriangles = 0; //  Numbre of triangles we are painting.

GLuint g_Vao2 = 0; 
GLuint g_NumTriangles2 = 0; 

GLuint g_Vao3 = 0; 
GLuint g_NumTriangles3 = 0;

GLuint g_Vao4 = 0; 
GLuint g_NumTriangles4 = 0;

GLuint g_Vao5 = 0; 
GLuint g_NumTriangles5 = 0;

GLuint g_Vao6 = 0; 
GLuint g_NumTriangles6 = 0;

GLuint g_Vao7 = 0; 
GLuint g_NumTriangles7 = 0;

GLuint g_Vao8 = 0; 
GLuint g_NumTriangles8 = 0;

GLuint g_Vao9 = 0; 
GLuint g_NumTriangles9 = 0;

GLuint g_Vao44 = 0; 
GLuint g_NumTriangles44 = 0;

GLuint g_Vao10 = 0; 
GLuint g_NumTriangles10 = 0;

GLuint g_Vao11 = 0; 
GLuint g_NumTriangles11 = 0;

vec3 sol = vec3(0.0f, 0.0f, 0.0f);  
vec3 mercury = vec3(1.5f, 0.0f, 0.0f); 
vec3 venus = vec3(2.3f, 0.0f, 0.0f);
vec3 terra = vec3(3.3f, 0.0f, 0.0f);
vec3 lluna = vec3(3.9f, 0.5f, 0.0f);

vec3 eye = vec3 (1.0f, 3.0f, 5.0f);
vec3 center = vec3(0.0f, 0.0f, 0.0f);
vec3 up = vec3(0.0f, 4.0f, 0.0f);

vec3 centerU = vec3(0.0f, 0.0f, -1.0f);
vec3 eyeU = vec3(0.0f, 0.0f, 0.0f);

GLuint texture_id;
GLuint texture_id2;
GLuint texture_id3;
GLuint texture_id4;
GLuint texture_id5;
GLuint texture_id6;
GLuint texture_id7;
GLuint texture_id8;
GLuint texture_id9;
GLuint texture_id44;
GLuint texture_id10;
GLuint texture_id11;

// ------------------------------------------------------------------------------------------
// This function manually creates a square geometry (defined in the array vertices[])
// ------------------------------------------------------------------------------------------
void load()
{
    
    string err;
    bool  ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), basepath.c_str());
    
    Shader simpleShader("src/shader.vert", "src/shader.frag");
    g_simpleShader = simpleShader.program;

    if (!err.empty()) { 
        std::cerr << err << std::endl;
    }
    else
        std::cout << "Loaded "<< inputfile << " with shapes: " << shapes.size() << std::endl;

    // Create the VAO where we store all geometry (stored in g_Vao)
    g_Vao = gl_createAndBindVAO();

    // Bind the vectors/arrays to the attributes in the shaders
	gl_createAndBindAttribute(&(shapes[0].mesh.positions[0]), shapes[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes[0].mesh.indices[0]), shapes[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes[0].mesh.texcoords[0]), shapes[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);


    gl_unbindVAO();

    g_NumTriangles = shapes[0].mesh.indices.size() / 3;

    Image* image = loadBMP("assets/sun.bmp");

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D,    //target
                  0,                //level = 0 base, no mipmap
                  GL_RGB,           //how the data will bee stored
                  image->width,     //width of the image
                  image->height,    //height of the image
                  0,                //border
                  GL_RGB,           //format of origianl data
                  GL_UNSIGNED_BYTE, //type of data
                  image->pixels
    );
    
    ////////////////////////////////////

    string err2;
    bool ret2 = tinyobj::LoadObj(shapes2, materials2, err2, inputfile2.c_str(), basepath.c_str());

    g_Vao2 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes2[0].mesh.positions[0]), shapes2[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes2[0].mesh.indices[0]), shapes2[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes2[0].mesh.texcoords[0]), shapes2[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles2 = shapes2[0].mesh.indices.size() /3;


    Image* image2 = loadBMP("assets/mercury.bmp");

    glGenTextures(1, &texture_id2);
    glBindTexture(GL_TEXTURE_2D, texture_id2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image2->width, image2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);

    //////////////////////////////////

    string err3;
    bool ret3 = tinyobj::LoadObj(shapes3, materials3, err3, inputfile3.c_str(), basepath.c_str());

    Shader simpleShader_sky("src/shader_sky.vert", "src/shader_sky.frag");
    g_simpleShader_sky = simpleShader_sky.program;  

    g_Vao3 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes3[0].mesh.positions[0]), shapes3[0].mesh.positions.size() * sizeof(float), g_simpleShader_sky, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes3[0].mesh.indices[0]), shapes3[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes3[0].mesh.texcoords[0]), shapes3[0].mesh.texcoords.size()* sizeof(GLfloat), g_simpleShader_sky, "a_uv", 2);

    gl_unbindVAO();
    g_NumTriangles3 = shapes3[0].mesh.indices.size() / 3;

    Image* imageU = loadBMP("assets/milkyway.bmp");

    glGenTextures(1, &texture_id3);
    glBindTexture(GL_TEXTURE_2D, texture_id3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageU->width, imageU->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageU->pixels);

    //////////////////////////////////

    string err4;
    bool ret4 = tinyobj::LoadObj(shapes4, materials4, err4, inputfile4.c_str(), basepath.c_str());

    g_Vao4 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes4[0].mesh.positions[0]), shapes4[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes4[0].mesh.indices[0]), shapes4[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes4[0].mesh.texcoords[0]), shapes4[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles4 = shapes4[0].mesh.indices.size() /3;


    Image* image4 = loadBMP("assets/venus.bmp");

    glGenTextures(1, &texture_id4);
    glBindTexture(GL_TEXTURE_2D, texture_id4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image4->width, image4->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->pixels);

    //////////////////////////////////

    string err5;
    bool ret5 = tinyobj::LoadObj(shapes5, materials5, err5, inputfile5.c_str(), basepath.c_str());

    g_Vao5 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes5[0].mesh.positions[0]), shapes5[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes5[0].mesh.indices[0]), shapes5[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes5[0].mesh.texcoords[0]), shapes5[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles5 = shapes5[0].mesh.indices.size() /3;


    Image* image5 = loadBMP("assets/earth.bmp");

    glGenTextures(1, &texture_id5);
    glBindTexture(GL_TEXTURE_2D, texture_id5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image5->width, image5->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->pixels);

    //////////////////////////////////

    string err6;
    bool ret6 = tinyobj::LoadObj(shapes6, materials6, err6, inputfile6.c_str(), basepath.c_str());

    g_Vao6 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes6[0].mesh.positions[0]), shapes6[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes6[0].mesh.indices[0]), shapes6[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes6[0].mesh.texcoords[0]), shapes6[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles6 = shapes6[0].mesh.indices.size() /3;


    Image* image6 = loadBMP("assets/moon.bmp");

    glGenTextures(1, &texture_id6);
    glBindTexture(GL_TEXTURE_2D, texture_id6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image6->width, image6->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image6->pixels);

    //////////////////////////////////

    string err7;
    bool ret7 = tinyobj::LoadObj(shapes7, materials7, err7, inputfile7.c_str(), basepath.c_str());

    g_Vao7 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes7[0].mesh.positions[0]), shapes7[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes7[0].mesh.indices[0]), shapes7[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes7[0].mesh.texcoords[0]), shapes7[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles7 = shapes7[0].mesh.indices.size() /3;


    Image* image7 = loadBMP("assets/mars.bmp");

    glGenTextures(1, &texture_id7);
    glBindTexture(GL_TEXTURE_2D, texture_id7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image7->width, image7->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image7->pixels);

    //////////////////////////////////

    string err8;
    bool ret8 = tinyobj::LoadObj(shapes8, materials8, err8, inputfile8.c_str(), basepath.c_str());

    g_Vao8 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes8[0].mesh.positions[0]), shapes8[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes8[0].mesh.indices[0]), shapes8[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes8[0].mesh.texcoords[0]), shapes8[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles8 = shapes8[0].mesh.indices.size() /3;


    Image* image8 = loadBMP("assets/jupiter.bmp");

    glGenTextures(1, &texture_id8);
    glBindTexture(GL_TEXTURE_2D, texture_id8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image8->width, image8->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image8->pixels);

    //////////////////////////////////

    string err9;
    bool ret9 = tinyobj::LoadObj(shapes9, materials9, err9, inputfile9.c_str(), basepath.c_str());

    g_Vao9 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes9[0].mesh.positions[0]), shapes9[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes9[0].mesh.indices[0]), shapes9[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes9[0].mesh.texcoords[0]), shapes9[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles9 = shapes9[0].mesh.indices.size() /3;

    Image* image9 = loadBMP("assets/saturn.bmp");

    glGenTextures(1, &texture_id9);
    glBindTexture(GL_TEXTURE_2D, texture_id9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image9->width, image9->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image9->pixels);

    //////////////////////////////////

    string err44;
    bool ret44 = tinyobj::LoadObj(shapes44, materials44, err44, inputfile44.c_str(), basepath.c_str());

    g_Vao44 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes44[0].mesh.positions[0]), shapes44[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes44[0].mesh.indices[0]), shapes44[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes44[0].mesh.texcoords[0]), shapes44[0].mesh.texcoords.size()* sizeof(GLfloat), g_simpleShader, "a_uv", 2);

    gl_unbindVAO();
    g_NumTriangles44 = shapes44[0].mesh.indices.size() / 3;

    Image* imageO = loadBMP("assets/saturn_rings.bmp");

    glGenTextures(1, &texture_id44);
    glBindTexture(GL_TEXTURE_2D, texture_id44);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageO->width, imageO->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageO->pixels);

    //////////////////////////////////

    string err10;
    bool ret10 = tinyobj::LoadObj(shapes10, materials10, err10, inputfile10.c_str(), basepath.c_str());

    g_Vao10 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes10[0].mesh.positions[0]), shapes10[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes10[0].mesh.indices[0]), shapes10[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes10[0].mesh.texcoords[0]), shapes10[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles10 = shapes10[0].mesh.indices.size() /3;


    Image* image10 = loadBMP("assets/uranus.bmp");

    glGenTextures(1, &texture_id10);
    glBindTexture(GL_TEXTURE_2D, texture_id10);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image10->width, image10->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image10->pixels);

    //////////////////////////////////

    string err11;
    bool ret11 = tinyobj::LoadObj(shapes11, materials11, err11, inputfile11.c_str(), basepath.c_str());

    g_Vao11 = gl_createAndBindVAO();

    gl_createAndBindAttribute(&(shapes11[0].mesh.positions[0]), shapes11[0].mesh.positions.size() * sizeof(float), g_simpleShader, "a_vertex", 3);
    gl_createIndexBuffer(&(shapes11[0].mesh.indices[0]), shapes11[0].mesh.indices.size() * sizeof(unsigned int));
    gl_createAndBindAttribute(&(shapes11[0].mesh.texcoords[0]), shapes11[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles11 = shapes11[0].mesh.indices.size() /3;


    Image* image11 = loadBMP("assets/neptune.bmp");

    glGenTextures(1, &texture_id11);
    glBindTexture(GL_TEXTURE_2D, texture_id11);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image11->width, image11->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image11->pixels);

}


void draw()
{
    
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    float rot = glfwGetTime();
    float rot2 =  glfwGetTime()/2;

    glUseProgram(g_simpleShader_sky);

    GLuint u_model = glGetUniformLocation(g_simpleShader_sky, "u_model");
    GLuint u_view = glGetUniformLocation(g_simpleShader_sky, "u_view");
    GLuint u_projection = glGetUniformLocation(g_simpleShader_sky, "u_projection");

    mat4 model_matrix = translate(mat4(1.0f), eyeU);
    mat4 view_matrix = lookAt(eyeU, centerU, vec3(0, 1, 0));
    mat4 projection_matrixU = glm::perspective(90.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);

    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
    glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrixU));

    GLuint u_texture3 = glGetUniformLocation(g_simpleShader_sky, "u_texture"); 
    glUniform1i(u_texture3, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id3);

    gl_bindVAO(g_Vao3);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles3, GL_UNSIGNED_INT, 0);

    ////////////////////////////////////// SOL
    glEnable(GL_DEPTH_TEST);

    glUseProgram(g_simpleShader);

    GLuint model_loc = glGetUniformLocation(g_simpleShader, "u_model");

	mat4 model = translate(mat4(1.0f), sol);	// x y z	
	mat4 model3 = scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model * model3));

	//create preojection matrix and pass to shader
	mat4 projection_matrix = perspective(
		90.0f,	//Field of view
		1.0f,	//Aspect ratio
		0.1f,	//near plane (distance from camera)
		50.0f	//Far plane (distance from camera)
	);
	GLuint projection_loc = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	mat4 view = glm::lookAt(eye, center, up);

	GLuint view_loc = glGetUniformLocation(g_simpleShader, "u_view");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint u_texture = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    gl_bindVAO(g_Vao);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// MERCURI

    glUseProgram(g_simpleShader);

    GLuint model_loc2 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius = 1.0f;
	float camX = sin(rot*3) * radius;
	float camZ = cos(rot*3) * radius;

	mat4 modelT2 = translate(mat4(1.0f), vec3(camX, camX, camZ));	// x y z
    mat4 model2 = rotate(mat4(1.0), rot*3, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT3 = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));
	glUniformMatrix4fv(model_loc2, 1, GL_FALSE, glm::value_ptr(modelT2 * modelT3 * model2));

    mat4 projection_matrix2 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc2 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc2, 1, GL_FALSE, glm::value_ptr(projection_matrix2));

    GLuint u_texture2 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture2, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id2);

    gl_bindVAO(g_Vao2);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles2, GL_UNSIGNED_INT, 0);    

    ///////////////////////////////////////// VENUS

    glUseProgram(g_simpleShader);

    GLuint model_loc4 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius4 = 1.5f;
	float camX4 = sin(rot*2) * radius4;
	float camZ4 = cos(rot*2) * radius4;

	mat4 modelT4 = translate(mat4(1.0f), vec3(camX4, camX4, camZ4));	// x y z
    mat4 modelT4r = rotate(mat4(1.0f), rot*2, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT34 = scale(mat4(1.0f), vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(model_loc4, 1, GL_FALSE, glm::value_ptr(modelT4 * modelT34 * modelT4r));

    mat4 projection_matrix4 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc4 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc4, 1, GL_FALSE, glm::value_ptr(projection_matrix4));

    GLuint u_texture4 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture4, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id4);

    gl_bindVAO(g_Vao4);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles4, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// TERRA

    glUseProgram(g_simpleShader);

    GLuint model_loc5 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius5 = 2.3f;
	float camX5 = sin(rot) * radius5;
	float camZ5 = cos(rot) * radius5;

	mat4 modelT5 = translate(mat4(1.0f), vec3(camX5, camX5, camZ5));	// x y z
    mat4 modelT5r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT35 = scale(mat4(1.0f), vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(model_loc5, 1, GL_FALSE, glm::value_ptr(modelT5 * modelT35 * modelT5r));

    mat4 projection_matrix5 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc5 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc5, 1, GL_FALSE, glm::value_ptr(projection_matrix5));

    GLuint u_texture5 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture5, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id5);

    gl_bindVAO(g_Vao5);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles5, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// LLUNA

    glUseProgram(g_simpleShader);

    GLuint model_loc6 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius62 = 3.9f;
    const float radius6 = 0.6f;
    float camX6 = (sin(rot*2) * radius6) + camX5;
	float camZ6 = (cos(rot*2) * radius6) + camZ5;

	mat4 modelT6 = translate(mat4(1.0f), vec3(camX6, camX6, camZ6));	// x y z
    mat4 modelT6r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT36 = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));
	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(modelT6 * modelT36 * modelT6r));

    mat4 projection_matrix6 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc6 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, glm::value_ptr(projection_matrix6));

    GLuint u_texture6 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture6, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id6);

    gl_bindVAO(g_Vao6);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles6, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// MART

    glUseProgram(g_simpleShader);

    GLuint model_loc7 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius7 = 3.2f;
    float camX7 = sin(rot/2) * radius7;
	float camZ7 = cos(rot/2) * radius7;

	mat4 modelT7 = translate(mat4(1.0f), vec3(camX7, camX7, camZ7));	// x y z
    mat4 modelT7r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT37 = scale(mat4(1.0f), vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(model_loc7, 1, GL_FALSE, glm::value_ptr(modelT7 * modelT37 * modelT7r));

    mat4 projection_matrix7 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc7 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc7, 1, GL_FALSE, glm::value_ptr(projection_matrix7));

    GLuint u_texture7 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture7, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id7);

    gl_bindVAO(g_Vao7);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles7, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// JUPITER

    glUseProgram(g_simpleShader);

    GLuint model_loc8 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius8 = 3.7f;
    float camX8 = sin(rot/3) * radius8;
	float camZ8 = cos(rot/3) * radius8;

	mat4 modelT8 = translate(mat4(1.0f), vec3(camX8, camX8, camZ8));	// x y z
    mat4 modelT8r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT38 = scale(mat4(1.0f), vec3(0.7f, 0.7f, 0.7f));
	glUniformMatrix4fv(model_loc8, 1, GL_FALSE, glm::value_ptr(modelT8 * modelT38 * modelT8r));

    mat4 projection_matrix8 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc8 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc8, 1, GL_FALSE, glm::value_ptr(projection_matrix8));

    GLuint u_texture8 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture8, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id8);

    gl_bindVAO(g_Vao8);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles8, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// SATURN

    glUseProgram(g_simpleShader);

    GLuint model_loc9 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius9 = 4.3f;
    float camX9 = sin(rot/4) * radius9;
	float camZ9 = cos(rot/4) * radius9;

	mat4 modelT9 = translate(mat4(1.0f), vec3(camX9, camX9, camZ9));	// x y z
    mat4 modelT9r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT39 = scale(mat4(1.0f), vec3(0.4f, 0.4f, 0.4f));
	glUniformMatrix4fv(model_loc9, 1, GL_FALSE, glm::value_ptr(modelT9 * modelT39 * modelT9r));

    mat4 projection_matrix9 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc9 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc9, 1, GL_FALSE, glm::value_ptr(projection_matrix9));

    GLuint u_texture9 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture9, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id9);

    gl_bindVAO(g_Vao9);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles9, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// ANELLS SATURN

    glUseProgram(g_simpleShader);

    GLuint model_loc44 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius44 = 4.3f;
    float camX44 = sin(rot/4) * radius44;
	float camZ44 = cos(rot/4) * radius44;

	mat4 modelT44 = translate(mat4(1.0f), vec3(camX44, camX44, camZ44));	// x y z
    mat4 modelT44r = rotate(mat4(1.0), 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT344 = scale(mat4(1.0f), vec3(1.7f, 1.7f, 1.7f));
	glUniformMatrix4fv(model_loc44, 1, GL_FALSE, glm::value_ptr(modelT44 * modelT344 * modelT44r));

    mat4 projection_matrix44 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc44 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc44, 1, GL_FALSE, glm::value_ptr(projection_matrix44));

    GLuint u_texture44 = glGetUniformLocation(g_simpleShader, "u_texture");
    glUniform1i(u_texture44, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id44);

    gl_bindVAO(g_Vao44);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles44, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// URÀ

    glUseProgram(g_simpleShader);

    GLuint model_loc10 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius10 = 4.5f;
    float camX10 = sin(rot/5) * radius10;
	float camZ10 = cos(rot/5) * radius10;

	mat4 modelT10 = translate(mat4(1.0f), vec3(camX10, camX10, camZ10));	// x y z
    mat4 modelT10r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT310 = scale(mat4(1.0f), vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(model_loc10, 1, GL_FALSE, glm::value_ptr(modelT10 * modelT310 * modelT10r));

    mat4 projection_matrix10 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc10 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc10, 1, GL_FALSE, glm::value_ptr(projection_matrix10));

    GLuint u_texture10 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture10, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id10);

    gl_bindVAO(g_Vao10);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles10, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////// NEPTÚ

    glUseProgram(g_simpleShader);

    GLuint model_loc11 = glGetUniformLocation(g_simpleShader, "u_model");

    const float radius11 = 4.7f;
    float camX11 = sin(rot/6) * radius11;
	float camZ11 = cos(rot/6) * radius11;

	mat4 modelT11 = translate(mat4(1.0f), vec3(camX11, camX11, camZ11));	// x y z
    mat4 modelT11r = rotate(mat4(1.0), rot, vec3(0.0f, 1.0f, 0.0f));
	mat4 modelT311 = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));
	glUniformMatrix4fv(model_loc11, 1, GL_FALSE, glm::value_ptr(modelT11 * modelT311 * modelT11r));

    mat4 projection_matrix11 = perspective(90.0f, 1.0f, 0.1f, 50.0f);
    GLuint projection_loc11 = glGetUniformLocation(g_simpleShader, "u_projection");
	glUniformMatrix4fv(projection_loc11, 1, GL_FALSE, glm::value_ptr(projection_matrix11));

    GLuint u_texture11 = glGetUniformLocation(g_simpleShader, "u_texture");

    glUniform1i(u_texture11, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id11);

    gl_bindVAO(g_Vao11);
    glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles11, GL_UNSIGNED_INT, 0);

}

// ------------------------------------------------------------------------------------------
// This function is called every time you press a screen
// ------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //quit
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    //reload
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        load();
}

// ------------------------------------------------------------------------------------------
// This function is called every time you click the mouse
// ------------------------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        cout << "Left mouse down at" << mouse_x << ", " << mouse_y << endl;
    }
}

int main(void)
{
    //setup window and boring stuff, defined in glfunctions.cpp
    GLFWwindow* window;
    if (!glfwInit())return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(g_ViewportWidth, g_ViewportHeight, "Hello OpenGL!", NULL, NULL);
    if (!window) {glfwTerminate();    return -1;}
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    //input callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    //load all the resources
    load();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        draw();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
        
        //mouse position must be tracked constantly (callbacks do not give accurate delta)
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }

    //terminate glfw and exit
    glfwTerminate();
    return 0;
}


