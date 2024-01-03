#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Load Image Texture
// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Matrix --> Transformation
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Audio
#include <irrklang/irrKlang.h>
using namespace irrklang;

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void langkah();

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(-15.0f, 24.0704f, -11.562f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mekanik lompat
int flag = 0;
int flagLompat = 0;
float coorBerdiri;

// Liat map
// --------
float lastx, lasty, lastz, lastyaw, lastpitch;

// Audio
// -----
ISoundEngine* SoundEngine = createIrrKlangDevice();
ISoundEngine* Engine = createIrrKlangDevice();

// Flag Screen
// -----------
int flagScreen = 1;

// Flag Pintu
// ----------
int flagDoor = 0;
float translateDoor1 = 0.0;
float translateDoor2 = 0.0;
float translateDoor3 = 0.0;
int button1 = 0, button2 = 0, button3 = 0;

// Monster
// -------
float tempatMonsterX = 0.0f;
float tempatMonsterZ = -115.431f;
float translateMonsterX = 0.0f;
float translateMonsterZ = 0.0f;
int flagMonster = 0;

// Flag Sound
// ----------
int flagSound = 0;

// Flag Map
// --------
int flagMap = 0;

// Flag Harta Karun
// ----------------
int flagHK = 0;

// Flag Perangkap
// --------------
float translatePerangkap = 0.0f;
float titikPerangkap = 11.338f;
int flagPerangkap = 0;
int flagSoundPerangkap = 0;

// Flag Langkah & Lompat
// ---------------------
int flagLangkah = 1;
int flagLompat2 = 0;

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Escape The Dungeon", NULL, NULL);
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

    // Pintu Level 1 - Level 2
    // -----------------------
    float pintu1[] = {
        // SISI BELAKANG
        3.0f, -2.92956f, -46.662f, 1.0f, 0.0f,
        3.0f, 1.07044f, -46.662f, 1.0f, 1.0f,
        -3.0f, 1.07044f, -46.662f, 0.0f, 1.0f,

        -3.0f, 1.07044f, -46.662f, 0.0f, 1.0f,
        -3.0f, -2.92956f, -46.662f, 0.0f, 0.0f,
        3.0f, -2.92956f, -46.662f, 1.0f, 0.0f,

        // SISI DEPAN
        3.0f, -2.92956f, -48.662f, 1.0f, 0.0f,
        3.0f, 1.07044f, -48.662f, 1.0f, 1.0f,
        -3.0f, 1.07044f, -48.662f, 0.0f, 1.0f,

        -3.0f, 1.07044f, -48.662f, 0.0f, 1.0f,
        -3.0f, -2.92956f, -48.662f, 0.0f, 0.0f,
        3.0f, -2.92956f, -48.662f, 1.0f, 0.0f,

        // SISI BAWAH
        3.0f, -2.92954f, -48.662f, 1.0f, 0.0f,
        3.0f, -2.92954f, -46.662f, 1.0f, 0.0f,
        -3.0f, -2.92954f, -46.662f, 0.0f, 0.0f,

        3.0f, -2.92954f, -48.662f, 1.0f, 0.0f,
        -3.0f, -2.92954f, -48.662f, 0.0f, 0.0f,
        -3.0f, -2.92954f, -46.662f, 0.0f, 0.0f,
    };

    float pintu2[] = {
        // SISI BAWAH
        -3.0f, -2.92954f, -106.662f, 0.0f, 0.0f,
        -3.0f, -2.92954f, -104.662f, 0.0f, 0.0f,
        3.0f, -2.92954f, -104.662f, 1.0f, 0.0f,

        -3.0f, -2.92954f, -106.662f, 0.0f, 0.0f,
        3.0f, -2.92954f, -106.662f, 1.0f, 0.0f,
        3.0f, -2.92954f, -104.662f, 1.0f, 0.0f,

        // SISI DEPAN
        3.0f, 1.07046f, -104.662f, 1.0f, 1.0f,
        -3.0f, 1.07046f, -104.662f, 0.0f, 1.0f,
        3.0f, -2.92954f, -104.662f, 1.0f, 0.0f,

        -3.0f, -2.92954f, -104.662f, 0.0f, 0.0f,
        -3.0f, 1.07046f, -104.662f, 0.0f, 1.0f,
        3.0f, -2.92954f, -104.662f, 1.0f, 0.0f,

        // SISI BELAKANG
        3.0f, 1.07046f, -106.662f, 1.0f, 1.0f,
        -3.0f, 1.07046f, -106.662f, 0.0f, 1.0f,
        3.0f, -2.92954f, -106.662f, 1.0f, 0.0f,

        -3.0f, -2.92954f, -106.662f, 0.0f, 0.0f,
        -3.0f, 1.07046f, -106.662f, 0.0f, 1.0f,
        3.0f, -2.92954f, -106.662f, 1.0f, 0.0f,
    };

    float pintu3[] = {
        // SISI DEPAN
        44.99f, -2.92956f, -114.344f, 0.0f, 0.0f,
        44.99f, 1.07044f, -114.344f, 0.0f,1.0f,
        44.99f, 1.07044f, -108.344f, 1.0f, 1.0f,

        44.99f, -2.92956f, -114.344f, 0.0f, 0.0f,
        44.99f, -2.92956f, -108.344f, 1.0f, 0.0f,
        44.99f, 1.07044f, -108.344f, 1.0f, 1.0f,

        // SISI BELAKANG
        46.99f, -2.92956f, -114.344f, 0.0f, 0.0f,
        46.99f, 1.07044f, -114.344f, 0.0f, 1.0f,
        46.99f, 1.07044f, -108.344f, 1.0f, 1.0f,

        46.99f, -2.92956f, -114.344f, 0.0f, 0.0f,
        46.99f, -2.92956f, -108.344f, 1.0f, 0.0f,
        46.99f, 1.07044f, -108.344f, 1.0f, 1.0f,

        // SISI BAWAH
        44.99f, -2.92956f, -114.356f, 0.0f, 0.0f,
        46.99f, -2.92956f, -114.356f, 0.0f, 0.0f,
        46.99f, -2.92956f, -108.356f, 0.0f, 0.0f,

        44.99f, -2.92956f, -114.356f, 0.0f, 0.0f,
        44.99f, -2.92956f, -108.356f, 0.0f, 0.0f,
        46.99f, -2.92956f, -108.356f, 0.0f, 0.0f,
    };

    float monster[] = {
        // SISI DEPAN
        -1.0f, -2.92956f, -114.431f, 0.0f, 0.0f,
        1.0f, -2.92956f, -114.431f, 1.0f, 0.0f,
        1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        -1.0f, -2.92956f, -114.431f, 0.0f, 0.0f,
        -1.0f, 0.070443f, -114.431f, 0.0f, 1.0f,
        1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        // SISI BELAKANG
        -1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        1.0f, -2.92956f, -116.431f, 1.0f, 0.0f,
        1.0f, 0.070443f, -116.431f, 1.0f, 1.0f,

        -1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        -1.0f, 0.070443f, -116.431f, 0.0f, 1.0f,
        1.0f, 0.070443f, -116.431f, 1.0f, 1.0f,

        // SISI KIRI
        -1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        -1.0f, -2.92956f, -114.431f, 1.0f, 0.0f,
        -1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        -1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        -1.0f, 0.070443f, -116.431f, 0.0f, 1.0f,
        -1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        // SISI KANAN
        1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        1.0f, -2.92956f, -114.431f, 1.0f, 0.0f,
        1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        1.0f, -2.92956f, -116.431f, 0.0f, 0.0f,
        1.0f, 0.070443f, -116.431f, 0.0f, 1.0f,
        1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,

        // SISI ATAS
        -1.0f, 0.070443f, -114.431f, 0.0f, 1.0f,
        1.0f, 0.070443f, -114.431f, 1.0f, 1.0f,
        1.0f, 0.070444f, -116.431f, 1.0f, 1.0f,

        -1.0f, 0.070443f, -114.431f, 0.0f, 1.0f,
        -1.0f, 0.070443f, -116.431f, 0.0f, 1.0f,
        1.0f, 0.070444f, -116.431f, 1.0f, 1.0f,
    };

    float hartaKarun[] = {
        // SISI DEPAN
        0.269925f, -1.66355f, 4.0681f, 1.0f, 0.0f,
        -0.269925f, -1.66355f, 4.0681f, 0.0f, 0.0f,
        -0.269925f, -1.1237f, 4.0681f, 0.0f, 1.0f,

        0.269925f, -1.66355f, 4.0681f, 1.0f, 0.0f,
        0.269925f, -1.1237f, 4.0681f, 1.0f, 1.0f,
        -0.269925f, -1.1237f, 4.0681f, 0.0f, 1.0f,

        // SISI BELAKANG
        0.269925f, -1.66355f, 4.60796f, 1.0f, 0.0f,
        -0.269925f, -1.66355f, 4.60796f, 0.0f, 0.0f,
        -0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,

        0.269925f, -1.66355f, 4.60796f, 1.0f, 0.0f,
        0.269925f, -1.1237f, 4.60796f, 1.0f, 1.0f,
        -0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,

        // SISI KANAN
        0.269925f, -1.66355f, 4.60796f, 0.0f, 0.0f,
        0.269925f, -1.66355f, 4.0681f, 1.0f, 0.0f,
        0.269925f, -1.1237f, 4.0681f, 1.0f, 1.0f,

        0.269925f, -1.66355f, 4.60796f, 0.0f, 0.0f,
        0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,
        0.269925f, -1.1237f, 4.0681f, 1.0f, 1.0f,

        // SISI KIRI
        -0.269925f, -1.66355f, 4.60796f, 0.0f, 0.0f,
        -0.269925f, -1.66355f, 4.0681f, 1.0f, 0.0f,
        -0.269925f, -1.1237f, 4.0681f, 1.0f, 1.0f,

        -0.269925f, -1.66355f, 4.60796f, 0.0f, 0.0f,
        -0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,
        -0.269925f, -1.1237f, 4.0681f, 1.0f, 1.0f,

        // SISI ATAS
        0.269925f, -1.1237f, 4.0681f, 1.0f, 0.0f,
        -0.269925f, -1.1237f, 4.0681f, 0.0f, 0.0f,
        -0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,

        0.269925f, -1.1237f, 4.0681f, 1.0f, 0.0f,
        0.269925f, -1.1237f, 4.60796f, 1.0f, 1.0f,
        -0.269925f, -1.1237f, 4.60796f, 0.0f, 1.0f,
    };

    float perangkap[] = {
        // SISI ATAS
        -5.0f, -1.92958f, 67.338f, 0.0f, 1.0f,
        5.0f, -1.92958f, 67.338f, 1.0f, 1.0f,
        -5.0f, -1.92958f, 11.338f, 0.0f, 0.0f,

        5.0f, -1.92958f, 11.338f, 1.0f, 0.0f,
        5.0f, -1.92958f, 67.338f, 1.0f, 1.0f,
        -5.0f, -1.92958f, 11.338f, 0.0f, 0.0f,

        // SISI KIRI
        -5.0f, -1.92956f, 11.338f, 1.0f, 0.0f,
        -5.0f, -3.92956f, 11.338f, 0.0f, 0.0f,
        -5.0f, -1.92956f, 67.338f, 1.0f, 1.0f,

        -5.0f, -3.92956f, 67.338f, 0.0f, 1.0f,
        -5.0f, -3.92956f, 11.338f, 0.0f, 0.0f,
        -5.0f, -1.92956f, 67.338f, 1.0f, 1.0f,

        // SISI KANAN
        5.0f, -1.92956f, 11.338f, 1.0f, 0.0f,
        5.0f, -3.92956f, 11.338f, 0.0f, 0.0f,
        5.0f, -1.92956f, 67.338f, 1.0f, 1.0f,

        5.0f, -3.92956f, 67.338f, 0.0f, 1.0f,
        5.0f, -3.92956f, 11.338f, 0.0f, 0.0f,
        5.0f, -1.92956f, 67.338f, 1.0f, 1.0f,

        // SISI DEPAN
        -5.0f, -1.92956f, 11.338f, 0.0f, 1.0f,
        5.0f, -1.92956f, 11.338f, 1.0f, 1.0f,
        5.0f, -3.92956f, 11.338f, 1.0f, 0.0f,

        -5.0f, -1.92956f, 11.338f, 0.0f, 1.0f,
        -5.0f, -3.92956f, 11.338f, 0.0f, 0.0f,
        5.0f, -3.92956f, 11.338f, 1.0f, 0.0f,
    };

    // Bind Pintu Level 1 - Level 2 dengan VAO
    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pintu1), pintu1, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind Pintu Level 2 - Level 3 dengan VAO
    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pintu2), pintu2, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind Pintu Level 3 - END dengan VAO
    unsigned int VBO3, VAO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pintu3), pintu3, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind Monster dengan VAO
    unsigned int VBO4, VAO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);

    glBindVertexArray(VAO4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(monster), monster, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind Harta Karun dengan VAO
    unsigned int VBO5, VAO5;
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);

    glBindVertexArray(VAO5);

    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hartaKarun), hartaKarun, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind Perangkap dengan VAO
    unsigned int VBO6, VAO6;
    glGenVertexArrays(1, &VAO6);
    glGenBuffers(1, &VBO6);

    glBindVertexArray(VAO6);

    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glBufferData(GL_ARRAY_BUFFER, sizeof(perangkap), perangkap, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2, texture3, texture4;
    // texture Pintu
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("C:/Users/nn/Downloads/pintu.jpg.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture Monster
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/nn/Downloads/Assets/monster.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture Harta Karun
    // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/nn/Downloads/Assets/HartaKarun.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture Perangkap
    // -----------------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("C:/Users/nn/Downloads/Assets/perangkap.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // load models
    // -----------
    Model ourModel("C:/Users/nn/Downloads/Assets/jalu.obj");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Untuk buat ilusi lompat
    float jump = 0.0f;

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        if (flagSound == 0)
        {
            // Background Audio
            // ----------------
            Engine->play2D("C:/Users/nn/Downloads/Assets/Background Music.mp3", true);
            flagSound = 1;
        }
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        if (flagLompat2 == 2)
        {
            SoundEngine->play2D("C:/Users/nn/Downloads/Assets/jump 2.mp3", false);
            flagLompat2 = 0;
        }
        if (flagScreen == 0)
        {
            if (flag == 2 || flag == 3)
            {
                camera.ProcessKeyboard(PASIF, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            }
            if (flag == 10)
            {
                flag = 1;
            }
            if (flag == 5 && glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
            {
                camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            }
            if (flag == 1 && glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
            {
                camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            }
        }
        else
        {
            if (flagScreen == 2)
            {
                camera.ProcessKeyboard(LOSESCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
                camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
                if (flagSound == 4)
                {
                    SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Losing.mp3", false);
                    flagSound = 5;
                }
            }
            else if (flagScreen == 3)
            {
                camera.ProcessKeyboard(WINSCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
                camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
                if (flagSound == 12)
                {
                    Engine->stopAllSounds();
                    SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Winning.mp3", false);
                    flagSound = 13;
                }
            }
        }

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection;
        if (flag == 5)
        {
            projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        }
        else
        {
            projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        }
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        if (flag == 0)
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            flag = 1;
        }

        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        if (flagDoor == -1)
        {
            translateDoor1 = 0;
            translateDoor2 = 0;
            translateDoor3 = 0;
            flagDoor = 0;
        }

        // Rendering Pintu
        // Audio Gate
        if (flagSound == 2)
        {
            SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Open Gate.mp3", false);
            flagSound = 3;
        }
        // Render pintu 1
        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(VAO1);
        if (flagDoor > 0)
        {
            if (translateDoor1 <= 3.8f) {
                translateDoor1 += 0.025f;
            }
            else if (translateDoor1 > 3.8f && flagDoor == 1)
            {
                flagDoor = 2;
            }
            glm::mat4 tDoor1 = glm::mat4(1.0f);
            tDoor1 = glm::translate(tDoor1, glm::vec3(0.0f, translateDoor1, 0.0f));
            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tDoor1));
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Rendering Pintu
        // Audio Gate
        if (flagSound == 6)
        {
            SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Open Gate.mp3", false);
            flagSound = 7;
        }
        // Render pintu 2
        glm::mat4 tDoor2 = glm::mat4(1.0f);
        if (flagDoor > 2)
        {
            if (translateDoor2 <= 3.8f) {
                translateDoor2 += 0.025f;
            }
            else if (translateDoor1 > 3.8f && flagDoor == 3)
            {
                flagDoor = 4;
            }
        }
        tDoor2 = glm::translate(tDoor2, glm::vec3(0.0f, translateDoor2, 0.0f));
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tDoor2));
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Rendering Pintu
        // Render pintu 3
        glm::mat4 tDoor3 = glm::mat4(1.0f);
        if (button1 == 1 && button2 == 1 && button3 == 1)
        {
            if (flagSound == 10)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Open Gate.mp3", false);
                flagSound = 11;
            }
            if (translateDoor3 <= 3.8f) {
                translateDoor3 += 0.025f;
            }
        }
        tDoor3 = glm::translate(tDoor3, glm::vec3(0.0f, translateDoor3, 0.0f));
        modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tDoor3));
        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Rendering Monster
        // Setup Translate Monster
        if (flagMonster == 0)
        {
            camera.ProcessKeyboard(MONSTER, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
        }
        else
        {
            camera.ProcessKeyboard(JUMPSCARE, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            if (flagSound == 8)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Jumpscare.mp3", false);
                flagSound = 9;
            }
        }
        // Translate Monster
        glm::mat4 monster = glm::mat4(1.0f);
        monster = glm::translate(monster, glm::vec3(translateMonsterX, 0.0f, translateMonsterZ));
        modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(monster));
        // Render Monster
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO4);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Audio Harta Karun
        if (flagHK == 2)
        {
            SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Picking Item.mp3", false);
            flagHK = 1;
        }
        // Translate Harta Karun
        glm::mat4 hk = glm::mat4(1.0f);
        if (flagHK == 0)
        {
            hk = glm::translate(hk, glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else
        {
            hk = glm::translate(hk, glm::vec3(0.0f, -3.0f, 0.0f));
        }
        modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hk));
        // Render Harta Karun
        glBindTexture(GL_TEXTURE_2D, texture3);
        glBindVertexArray(VAO5);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Translasi Perangkap
        glm::mat4 perangkap = glm::mat4(1.0f);
        if (flagHK == 1 && flagPerangkap == 0)
        {
            if (flagSoundPerangkap == 0)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Perangkap.mp3", true);
                flagSoundPerangkap = 1;
            }
            if (translatePerangkap > -58.0f)
            {
                translatePerangkap -= 0.25f;
                titikPerangkap -= 0.25f;
            }
            else
            {
                flagPerangkap = 2;
                SoundEngine->stopAllSounds();
            }
        }
        perangkap = glm::translate(perangkap, glm::vec3(0.0f, 0.0f, translatePerangkap));
        modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(perangkap));
        if (flagPerangkap != 1)
        {
            camera.ProcessKeyboard(PASIF, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
        }
        if (flagPerangkap == 1)
        {
            if (flagSoundPerangkap == 1)
            {
                SoundEngine->stopAllSounds();
                flagSoundPerangkap = 0;
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Losing.mp3", false);
            }
            camera.ProcessKeyboard(PERANGKAPSCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
        }
        // Render Perangkap
        glBindTexture(GL_TEXTURE_2D, texture4);
        glBindVertexArray(VAO6);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (flag != 5 && flagScreen == 0 && flagMonster == 0 && (flagPerangkap == 0 || flagPerangkap == 2))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(FORWARD, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            langkah();
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            camera.ProcessKeyboard(BACKWARD, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            langkah();
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        {
            camera.ProcessKeyboard(LEFT, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            langkah();
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        {
            camera.ProcessKeyboard(RIGHT, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            langkah();
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        {
            camera.ProcessKeyboard(JUMP, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            if (flagLompat2 == 0) 
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/jump 1.mp3", false);
                flagLompat2 = 1;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) 
        {
            if (((camera.Position.x > -4.41738f && camera.Position.x < -1.99088f) && (camera.Position.z > -130.336f && camera.Position.z < -128.336f)) && button1 == 0)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/clickButton.mp3", false);
            }
            else if (((camera.Position.x > 6.33451f && camera.Position.x < 8.76101f) && (camera.Position.z > -142.538f && camera.Position.z < -138.538f)) && button2 == 0)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/clickButton.mp3", false);
            }
            else if (((camera.Position.x > 32.5381f && camera.Position.x < 34.9646f) && (camera.Position.z > -158.28f && camera.Position.z < -156.28f)) && button3 == 0)
            {
                SoundEngine->play2D("C:/Users/nn/Downloads/Assets/clickButton.mp3", false);
            }
            camera.ProcessKeyboard(OPENDOOR, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            camera.ProcessKeyboard(PICKITEM, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
    }
    if (flagMap == 0)
    {
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(SHOWMAP, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(CLOSEMAP, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            flagMap = 1;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (flagPerangkap == 1)
        {
            camera.ProcessKeyboard(ENDPERANGKAPSCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            SoundEngine->stopAllSounds();
            titikPerangkap = 11.338f;
            translatePerangkap = 0;
        }
        if (flagMonster == 1)
        {
            camera.ProcessKeyboard(ENDJUMPSCARE, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            SoundEngine->stopAllSounds();
        }
        if (flagScreen == 1)
        {
            camera.ProcessKeyboard(BEGINSCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
        }
        else if (flagScreen == 2)
        {
            camera.ProcessKeyboard(ENDLOSESCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            SoundEngine->stopAllSounds();
        }
        else if (flagScreen == 3)
        {
            camera.ProcessKeyboard(ENDWINSCREEN, deltaTime, &flag, &flagLompat, &coorBerdiri, &lastx, &lasty, &lastz, &lastpitch, &lastyaw, &flagScreen, &flagDoor, &button1, &button2, &button3, &tempatMonsterX, &tempatMonsterZ, &translateMonsterX, &translateMonsterZ, &flagMonster, &flagSound, &flagHK, titikPerangkap, &flagPerangkap, &flagLompat2);
            camera.ProcessMouseMovement(0.0f, 0.0f, &flag);
            SoundEngine->stopAllSounds();
            flagMap = 0;
            translatePerangkap = 0;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (flag != 5 && flagScreen == 0 && flagMonster == 0 && (flagPerangkap == 0 || flagPerangkap == 2))
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

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

        camera.ProcessMouseMovement(xoffset, yoffset, &flag);
    }
}

void langkah() 
{
    if (flagLangkah == 1 && !SoundEngine->isCurrentlyPlaying("C:/Users/nn/Downloads/Assets/Footsteps 2.mp3") && !SoundEngine->isCurrentlyPlaying("C:/Users/nn/Downloads/Assets/Footstep 1.mp3") && flagLompat == 0)
    {
        SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Footstep 1.mp3", false);
        flagLangkah = 2;
    }
    if (flagLangkah == 2 && !SoundEngine->isCurrentlyPlaying("C:/Users/nn/Downloads/Assets/Footsteps 2.mp3") && !SoundEngine->isCurrentlyPlaying("C:/Users/nn/Downloads/Assets/Footstep 1.mp3") && flagLompat == 0)
    {
        SoundEngine->play2D("C:/Users/nn/Downloads/Assets/Footsteps 2.mp3", false);
        flagLangkah = 1;
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}