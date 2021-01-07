#include <epoxy/gl.h>
#include <epoxy/glx.h>

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 mySpherePos;
glm::vec3 initialPos;
#include "Libraries/shader_m.h"
#include "Libraries/camera.h"
#include "Libraries/kolory.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <unordered_set>
#include <algorithm>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int n;
namespace RAND{
  std::mt19937 rng(0);
  
  void set_seed(int seed){
    rng = std::mt19937(seed);
  }

  int rand_int(int a, int b){
    return std::uniform_int_distribution<int>(a, b)(rng);
  }

  float rand_float(float a, float b){
    return std::uniform_real_distribution<float>(a, b)(rng);
  }
}

// lighting
// glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// my bybble
// mySpherePos is declared in camera.h
float sufit = 10;
float R = 0.25;
int ile_kul = 15;
const int ile_shiny = 20; // tę wartość trzeba dodać do shaderów

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

struct Bubble{
  glm::vec3 position;
  int       color_id;
  float     speed;
  float     radius; // equals initial scale
  bool shines = false;

  Bubble() {}
  Bubble(glm::vec3 p, int id, float sp, float ra) 
         : position(p), color_id(id), speed(sp), radius(ra) {}

  float promien_teraz(){
    return radius * (1.0 + 0.3 * (position.y + sufit) / (sufit * 2.0));
  }
};

float len(glm::vec3 a){
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

bool Bubble_intersection(glm::vec3 poz1, glm::vec3 poz2, float radius1, float radius2){
    return len(poz1 - poz2) < radius1 + radius2;
}

std::vector< Bubble > bubbles;

void move_bubbles_up(float deltaTime){
    for(int i = 0; i < bubbles.size(); i++){
        bubbles[i].position.y += deltaTime * bubbles[i].speed;
        if(bubbles[i].position.y > sufit)
            bubbles[i].position.y = -sufit;
    }
}

float sphereVertices[100000];

void add_vertex(int nr, glm::vec4 vec){
    sphereVertices[nr * 6] = sphereVertices[nr * 6 + 3] = vec.x;
    sphereVertices[nr * 6 + 1] = sphereVertices[nr * 6 + 4] = vec.y;
    sphereVertices[nr * 6 + 2] = sphereVertices[nr * 6 + 5] = vec.z;
}

int number_of_vertices_in_sphere = 0;

void generate_sphere(){
    // Gen sphere vertices
    float dok = 3;
    
    glm::mat4 trans_left = glm::mat4(1.0f);
    trans_left = glm::rotate(trans_left, glm::radians(dok), glm::vec3(0.0f, 1.0f, 0.0f));

    for(float i = -90; i <= 90 - dok; i += dok){
        glm::mat4 trans_vert = glm::mat4(1.0f);
        trans_vert = glm::rotate(trans_vert, glm::radians(i), glm::vec3(0.0f, 0.0f, 1.0f));  
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        vec = trans_vert * vec;

        glm::mat4 trans_vert2 = glm::mat4(1.0f);
        trans_vert2 = glm::rotate(trans_vert2, glm::radians((i + dok)), glm::vec3(0.0f, 0.0f, 1.0f));  
        glm::vec4 vec2(1.0f, 0.0f, 0.0f, 1.0f);
        vec2 = trans_vert2 * vec2;
        
        for(int j = 0; j <= 360 / dok; j++){
            add_vertex(number_of_vertices_in_sphere++, vec);
            vec = trans_left * vec;
            add_vertex(number_of_vertices_in_sphere++, vec2);
            vec2 = trans_left * vec2;
        }
    }
}

void markShiny(){    
    std::unordered_set<int> swiecace;
    while(swiecace.size() < ile_shiny)
        swiecace.insert(RAND::rand_int(0, ile_kul - 1));
    for(auto & u : swiecace)
        bubbles[u].shines = 1;
}

void generate_bubble_positions(){
    for(int i = 0; i < ile_kul; i++)
        bubbles.emplace_back( glm::vec3(RAND::rand_float(-sufit, sufit), 
                                        RAND::rand_float(-sufit, sufit),
                                        RAND::rand_float(-sufit + 3, sufit - 3)),
                              RAND::rand_int(0, kolorki.size() - 1),
                              RAND::rand_float(1.0f, 4.0f),
                              RAND::rand_float(0.2f, 0.6f)
        );
}

void setLight(Shader & shader){
    // directional light   
    shader.setVec3("dirLight.direction", 0.2f, -1.0f, -0.1f);
    shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("dirLight.diffuse", 1.2f, 1.2f, 1.2f);
    shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    //shiny bubbles
    int cnt = 0;
    for(auto & u : bubbles){
        if(!u.shines)
            continue;
        shader.setVec3("pointLights[" + std::to_string(cnt) + "].position", u.position);
        shader.setVec3("pointLights[" + std::to_string(cnt) + "].ambient", kolorki[u.color_id].first[0]);
        shader.setVec3("pointLights[" + std::to_string(cnt) + "].diffuse", kolorki[u.color_id].first[1]);
        shader.setVec3("pointLights[" + std::to_string(cnt) + "].specular", kolorki[u.color_id].first[2]);
        shader.setFloat("pointLights[" + std::to_string(cnt) + "].constant", 1.0f);
        shader.setFloat("pointLights[" + std::to_string(cnt) + "].linear", 0.09);
        shader.setFloat("pointLights[" + std::to_string(cnt) + "].quadratic", 0.032);

        cnt++;
    }
}

bool defaultCamera = true;

glm::vec3 getCameraPosition(){
    if(defaultCamera)
        return camera.Position;
    else
        return glm::vec3(sufit - 0.1, sufit - 0.1, - sufit + 0.1);
}

glm::mat4 getCameraViewMatrix(){
    if(defaultCamera)
        return camera.GetViewMatrix();
    else
        return glm::lookAt(getCameraPosition(), getCameraPosition() + glm::vec3(-1, -1, 1), glm::vec3(0.0f, 1.0f, 0.0f));
}

bool hidden = true;
float last_change = -1.0;

bool notTooFrequent(){
    return glfwGetTime() - last_change > 0.1;
}

glm::vec3 endPos;
float endR;

int main(int argc, char**argv)
{
    assert(argc >= 1 and argc <= 3);
    n = (argc >= 2 ? std::stoi(argv[1]) : 7);
    sufit = n;
    ile_kul = n * n;

    int seed = (argc >= 3 ? std::stoi(argv[2]) : 1);
    assert(n >= 5);
    initialPos = glm::vec3(0, 0, sufit - 2.5);
    endPos = glm::vec3(0, 0, - sufit - n * 0.5);
    endR = n / 1.5;

    mySpherePos = initialPos;
    camera.Position = mySpherePos - camera.Front * 2.0f;


    RAND::set_seed(seed);
    std::cout << std::setprecision(3) << std::fixed;

    generate_sphere();
    generate_bubble_positions();
    markShiny();
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    //enable reansparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      
    
    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("Shaders/multiple_lights_texture.vs", "Shaders/multiple_lights_texture.fs");
    Shader lightingShaderNoTextures("Shaders/multiple_lights.vs", "Shaders/multiple_lights.fs");
    Shader lightCubeShader("Shaders/light_cube.vs", "Shaders/light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // first, configure the cube's VAO (and VBO)
    unsigned int cubeVBO, sphereVBO; 
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &sphereVBO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) * number_of_vertices_in_sphere, sphereVertices, GL_STATIC_DRAW);

    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // cubes without textures
    unsigned int sphereVAO;
    glGenVertexArrays(1, &sphereVAO);    
    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("Textures/Ocean.png");
    unsigned int specularMap = loadTexture("Textures/Specular.png");

    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    // render loop
    // -----------
    int finishCounter = 60;

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", getCameraPosition());
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        setLight(lightingShader);  

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = getCameraViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        // render background
        glBindVertexArray(cubeVAO);
            // calculate the model matrix for each object and pass it to shader before drawing
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(2 * sufit + 3));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // ---------------------------------- Generowanie mojej kuli ------------------------------------
        
        lightingShaderNoTextures.use();
        lightingShaderNoTextures.setVec3("viewPos", getCameraPosition());
        lightingShaderNoTextures.setFloat("material.shininess", 32.0f);
        lightingShaderNoTextures.setVec3("material.ambient", kolorki[BRONZE].first[0]);
        lightingShaderNoTextures.setVec3("material.diffuse", kolorki[BRONZE].first[1]);
        lightingShaderNoTextures.setVec3("material.specular", kolorki[BRONZE].first[2]);
        lightingShaderNoTextures.setFloat("alpha", 1.0);

        setLight(lightingShaderNoTextures);

        lightingShaderNoTextures.setMat4("projection", projection);
        lightingShaderNoTextures.setMat4("view", view);

        // render containers
        {
            glBindVertexArray(sphereVAO);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, mySpherePos);
            model = glm::scale(model, glm::vec3(R));
            lightingShaderNoTextures.setMat4("model", model);
        }
        glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices_in_sphere);

        // ------------------------------------- Renderowanie końcowej kuli -----------------------------
        lightingShaderNoTextures.use();
        lightingShaderNoTextures.setVec3("viewPos", getCameraPosition());
        lightingShaderNoTextures.setFloat("material.shininess", 32.0f);
        lightingShaderNoTextures.setVec3("material.ambient", kolorki[YELLOW_PLASTIC].first[0]);
        lightingShaderNoTextures.setVec3("material.diffuse", kolorki[YELLOW_PLASTIC].first[1]);
        lightingShaderNoTextures.setVec3("material.specular", kolorki[YELLOW_PLASTIC].first[2]);
        lightingShaderNoTextures.setFloat("alpha", 1.0);

        setLight(lightingShaderNoTextures);

        lightingShaderNoTextures.setMat4("projection", projection);
        lightingShaderNoTextures.setMat4("view", view);

        {
            glBindVertexArray(sphereVAO);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, endPos);
            model = glm::scale(model, glm::vec3(endR));
            lightingShaderNoTextures.setMat4("model", model);
        }
        glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices_in_sphere);

        // -------------------------------- Generowanie Bąłbełków Świecacych ------------------------------------

         // also draw the lamp object(s)
         lightCubeShader.use();
         lightCubeShader.setMat4("projection", projection);
         lightCubeShader.setMat4("view", view);
        lightingShaderNoTextures.setFloat("alpha", 1.0);
    
         // we now draw as many light bulbs as we have point lights.
         glBindVertexArray(sphereVAO);
         for (unsigned int i = 0; i < bubbles.size(); i++)
         {  
            if(!bubbles[i].shines)
                continue;

            glm::mat4 model(1.0f);
            model = glm::translate(model, bubbles[i].position);
            model = glm::scale(model, glm::vec3(bubbles[i].promien_teraz()) );
            lightCubeShader.setMat4("model", model);
            lightCubeShader.setVec3("col", kolorki[bubbles[i].color_id].first[1]);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices_in_sphere);
        }

        // ------------------------------ Generowanie Bąłbełków Nieswiecacych ------------------------------
        lightingShaderNoTextures.use();
        lightingShaderNoTextures.setVec3("viewPos", getCameraPosition());
        lightingShaderNoTextures.setFloat("alpha", 0.4);
        std::sort(bubbles.begin(), bubbles.end(), [](const Bubble & a, const Bubble & b){
            return len(a.position - getCameraPosition()) > len(b.position - getCameraPosition());
        });

        setLight(lightingShaderNoTextures);

        lightingShaderNoTextures.setMat4("projection", projection);
        lightingShaderNoTextures.setMat4("view", view);

        glBindVertexArray(sphereVAO);
        for (unsigned int i = 0; i < bubbles.size(); i++){
            if(bubbles[i].shines)
                continue;

            lightingShaderNoTextures.setVec3("material.ambient", kolorki[bubbles[i].color_id].first[0]);
            lightingShaderNoTextures.setVec3("material.diffuse", kolorki[bubbles[i].color_id].first[1]);
            lightingShaderNoTextures.setVec3("material.specular", kolorki[bubbles[i].color_id].first[2]);
            lightingShaderNoTextures.setFloat("material.shininess", kolorki[bubbles[i].color_id].second);
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, bubbles[i].position);
            model = glm::scale(model, glm::vec3(bubbles[i].promien_teraz()) );
            lightingShaderNoTextures.setMat4("model", model);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, number_of_vertices_in_sphere);
        }

        move_bubbles_up(deltaTime);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        if(glfwWindowShouldClose(window) and finishCounter > 0){
          GLint m_viewport[4];
          glGetIntegerv( GL_VIEWPORT, m_viewport );

          glViewport(m_viewport[0] + m_viewport[2] / 85 , m_viewport[1] + m_viewport[3] / 85,
                     m_viewport[2] * 0.98, m_viewport[3] * 0.98);
          finishCounter -= 1;
        }

        // checking if reset
        for(auto & u : bubbles)
            if(Bubble_intersection(mySpherePos, u.position, R, u.promien_teraz())){
                mySpherePos = initialPos;
                camera.Position = mySpherePos - camera.Front * 2.0f;

                break;
            }

        // next lexel
        if(Bubble_intersection(mySpherePos, endPos, R, endR) and notTooFrequent()){
            mySpherePos = initialPos;
            camera.Position = mySpherePos - camera.Front * 2.0f;
            last_change = glfwGetTime();
            generate_bubble_positions();
        }
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &sphereVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        camera.ChangeMouseInputMode(window, hidden, last_change);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        if(glfwGetTime() - last_change > 0.1){
            defaultCamera ^= 1;
            last_change = glfwGetTime();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
        last_change = glfwGetTime();
        generate_bubble_positions();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    int windowHeight = std::min(height, (int)(width * SCR_HEIGHT / SCR_WIDTH));
    int windowWidth = std::min(width, (int)(height * SCR_WIDTH / SCR_HEIGHT));
    int diff_poz = (width - windowWidth) / 2;
    int diff_pion = (height - windowHeight) / 2;

    glViewport(diff_poz, diff_pion, windowWidth, windowHeight);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{   
    if(!hidden)
        return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else{
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}