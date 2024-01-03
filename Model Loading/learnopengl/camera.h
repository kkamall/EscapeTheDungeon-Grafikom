#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    PASIF,
    SHOWMAP,
    CLOSEMAP,
    BEGINSCREEN,
    LOSESCREEN,
    WINSCREEN,
    PERANGKAPSCREEN,
    ENDLOSESCREEN,
    ENDWINSCREEN,
    ENDPERANGKAPSCREEN,
    OPENDOOR,
    MONSTER,
    JUMPSCARE,
    ENDJUMPSCARE,
    PICKITEM
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 8.0f;
const float SENSITIVITY = 0.075f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime, int* flag, int *flagLompat, float *coorBerdiri, float *lastx, float *lasty, float *lastz, float *lastpitch, float *lastyaw, int *flagScreen, int *flagDoor, int *button1, int *button2, int *button3, float *tempatMonsterX, float *tempatMonsterZ, float *translateMonsterX, float * translateMonsterZ, int *flagMonster, int *flagSound, int *flagHK, float titikPerangkap, int *flagPerangkap, int *flagLompat2)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        if (direction == JUMP && *flag != 2) 
        {
            *flag = 2;
            *coorBerdiri = Position.y;
        }

// Fitur perangkap
        if (Position.z >= titikPerangkap && *flagPerangkap != 2) 
        {
            *flagPerangkap = 1;
        }

// Fitur membuka pintu
        if (direction == OPENDOOR) 
        {
            if ((Position.x < -2.34571f && Position.x > -4.7804f) && (Position.z < -44.662f && Position.z > -46.662f))
            {
                *flagDoor = 1;
                if (*flagSound == 1) 
                {
                    *flagSound = 2;
                }
            }
            if ((Position.x < -2.34571f && Position.x > -4.7804f) && (Position.z < -102.662f && Position.z > -104.662f))
            {
                *flagDoor = 3;
                if (*flagSound == 5 || *flagSound == 3) 
                {
                    *flagSound = 6;
                }
            }
            if ((Position.x > -4.41738f && Position.x < -1.99088f) && (Position.z > -130.336f && Position.z < -128.336f))
            {
                *button1 = 1;
            }
            if ((Position.x > 6.33451f && Position.x < 8.76101f) && (Position.z > -142.538f && Position.z < -138.538f))
            {
                *button2 = 1;
            }
            if ((Position.x > 32.5381f && Position.x < 34.9646f) && (Position.z > -158.28f && Position.z < -156.28f))
            {
                *button3 = 1;
            }
        }
        
// Fitur Screen
        // Keluar dari begin Screen
        if (direction == BEGINSCREEN) 
        {
            Position.x = 0.0f;
            Position.y = 0.92957f;
            Position.z = -11.662f;
            *flagScreen = 0;
        }
    // Losing Screen
        // Masuk Losing Screen
        if (direction == LOSESCREEN) 
        {
            Position.x = 15.0f;
            Position.y = 24.0704f;
            Position.z = -11.562f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagScreen = 2;
            if (*flagSound == 3 || *flagSound == 7) 
            {
                *flagSound = 4;
            }
        }
        // Keluar Losing Screen
        if (direction == ENDLOSESCREEN) 
        {
            Position.x = -0.019923f;
            Position.y = -0.989580f;
            Position.z = -49.679085f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagScreen = 0;
            *flag = 1;
            if (*flagDoor > 3) 
            {
                *flagSound = 7;
            }
            else 
            {
                *flagSound = 3;
            }
        }
    // Perangkap Screen
        // Masuk Perangkap Screen
        if(direction == PERANGKAPSCREEN)
        {
            Position.x = 51.0f;
            Position.y = 24.0704f;
            Position.z = -11.562f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagPerangkap = 1;
        }
        // Keluar Perangkap Screen
        if (direction == ENDPERANGKAPSCREEN) 
        {
            Position.x = 0.0f;
            Position.y = 0.92957f;
            Position.z = -11.662f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagDoor = -1;
            *flagScreen = 0;
            *flagHK = 0;
            *flagPerangkap = 0;
            *flagSound = 1;
        }
    // Winning Screen
        // Masuk Winning Screen
        if (direction == WINSCREEN) 
        {
            Position.x = -34.0f;
            Position.y = 24.0704f;
            Position.z = -11.562f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagScreen = 3;
            if (*flagSound == 11) 
            {
                *flagSound = 12;
            }
        }
        if (direction == ENDWINSCREEN) 
        {
            Position.x = 0.0f;
            Position.y = 0.92957f;
            Position.z = -11.662f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *tempatMonsterX = 0.0f;
            *tempatMonsterZ = -115.431f;
            *translateMonsterX = 0.0f;
            *translateMonsterZ = 0.0f;
            *flagDoor = -1;
            *flagScreen = 0;
            *button1 = 0;
            *button2 = 0;
            *button3 = 0;
            *flagSound = 0;
            *flagHK = 0;
            *flagPerangkap = 0;
        }
    // Jumpscare Screen
        if (direction == JUMPSCARE) 
        {
            Position.x = 33.0f;
            Position.y = 24.0704f;
            Position.z = -11.562f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *flagMonster = 1;
            if (*flagSound == 7 || *flagSound == 11) 
            {
                *flagSound = 8;
            }
        }
        if (direction == ENDJUMPSCARE) 
        {
            Position.x = -0.019923f;
            Position.y = -0.989580f;
            Position.z = -107.431f;
            Yaw = -90.0f;
            Pitch = 0.0f;
            *tempatMonsterX = 0.0f;
            *tempatMonsterZ = -115.431f;
            *translateMonsterX = 0.0f;
            *translateMonsterZ = 0.0f;
            *flagMonster = 0;
            if (*button1 == 1 && *button2 == 1 && *button3 == 1) 
            {
                *flagSound = 11;
            }
            else 
            {
                *flagSound = 7;
            }
        }

// Fitur Map
        // Buka Map
        if ((Position.x <= 7.0f && Position.x >= -7.0f) && (Position.z >= -104.662f && Position.z <= -98.662f))
        {
            if (direction == SHOWMAP && *flag != 5) 
            {
                *flag = 5;
                *lastx = Position.x;
                *lasty = Position.y;
                *lastz = Position.z;
                *lastpitch = Pitch;
                *lastyaw = Yaw;
                Position.x = 0.0f;
                Position.y = 24.0704f;
                Position.z = -17.81f;
                Yaw = -90.0f;
                Pitch = 0.0f;
            }
        }

        // Tutup MAP
        if (direction == CLOSEMAP && *flag == 5) 
        {
            Position.x = *lastx;
            Position.y = *lasty;
            Position.z = *lastz;
            Pitch = *lastpitch;
            Yaw = *lastyaw;
            *flag = 1;
        }

// Mekanik Monster
        if (Position.z < -106.662f && direction == MONSTER)
        {
            // Setup Translate Monster
            if (*tempatMonsterX < Position.x)
            {
                *tempatMonsterX += 0.14f;
                *translateMonsterX += 0.14f;
            }
            if (*tempatMonsterX > Position.x)
            {
                *tempatMonsterX -= 0.14f;
                *translateMonsterX -= 0.14f;
            }
            if (*tempatMonsterZ < Position.z)
            {
                *tempatMonsterZ += 0.14f;
                *translateMonsterZ += 0.14f;
            }
            if (*tempatMonsterZ > Position.z)
            {
                *tempatMonsterZ -= 0.14f;
                *translateMonsterZ -= 0.14f;
            }
            if ((*tempatMonsterX > Position.x - 0.2f && *tempatMonsterX < Position.x) && (*tempatMonsterZ > Position.z - 0.2f && *tempatMonsterZ < Position.z))
            {
                *flagMonster = 1;
            }
        }

// Mekanik Jatuh Parkour
        if (*flag == 3) 
        {
            Position.y -= 0.15f;
            if (Position.y < -7.92958f)
            {
                *flagScreen = 2;
            }
        }

// Mekanik lompat
        if (*flag == 2) 
        {
            if (*flagLompat == 0) 
            {
                Position.y += 0.1f;
                if (Position.y > *coorBerdiri + 4.0f) 
                {
                    *flagLompat = 1;
                }
            }
            if (*flagLompat == 1) 
            {
                Position.y -= 0.1f;

    // Level 0 & 1-belakang
                if (((Position.x >= -7.0f && Position.x <= 7.0f) && (Position.y >= -52.662f && Position.y <= +9.33803f)) || ((Position.x < 49.0054f && Position.x > -31.0f) && (Position.z < -106.662f && Position.z > -164.431f)))
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }

    // Level 1
        // Level 1 Parkour
                // Balok 1
                if ((Position.x >= -1.0f && Position.x <= 1.0f) && (Position.z <= -52.662f && Position.z >= -56.662f) && Position.y >= -0.92958f)
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 2
                if ((Position.x <= -1.0f && Position.x >= -7.0f) && (Position.z <= -54.662f && Position.z >= -56.662f))
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 3
                if ((Position.x <= -5.0f && Position.x >= -7.0f) && (Position.z <= -56.662f && Position.z >= -62.662f))
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 4
                if ((Position.x <= 7.0f && Position.x >= -5.0f) && (Position.z <= -60.662f && Position.z >= -62.662f))
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }

        // Level 2 Parkour
                // Balok 1
                if ((Position.x <= 6.0f && Position.x >= 2.0f) && (Position.z <= -64.662f && Position.z >= -68.662f))
                {
                    if (Position.y < -0.92958f)
                    {
                        Position.y = -0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 2
                if ((Position.x <= 3.0f && Position.x >= -1.0f) && (Position.z <= -69.662f && Position.z >= -73.662f))
                {
                    if (Position.y < 0.92958f)
                    {
                        Position.y = 0.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 3
                if ((Position.x <= 0.0f && Position.x >= -4.0f) && (Position.z <= -74.662f && Position.z >= -78.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }

        // Level 3 Parkour
                // Balok 1
                if ((Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -79.662f && Position.z >= -81.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 2
                if ((Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -84.662f && Position.z >= -86.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 3
                if ((Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 4
                if ((Position.x <= 1.0f && Position.x >= -1.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                // Balok 5
                if ((Position.x <= 6.0f && Position.x >= 4.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
                //Balok 6
                if ((Position.x <= 6.0f && Position.x >= 4.0f) && (Position.z <= -94.662f && Position.z >= -96.662f))
                {
                    if (Position.y < 1.92958f)
                    {
                        Position.y = 1.92958f;
                        *flagLompat = 0;
                        *flagLompat2 = 2;
                        *flag = 1;
                    }
                }
            }
        }

// Tidak menembus dinding
        // Level 0
        if (*flagScreen == 0 && *flagMonster == 0 && *flagPerangkap == 0) 
        {
            if (*flagDoor < 2) 
            {
                if (Position.z < -46.162f) 
                {
                    Position.z = -46.162f;
                }
            }
            if (Position.z >= -48.662f && *flag != 5)
            {
                if (*flagHK == 0) 
                {
                    if (Position.z < -46.162f)
                    {
                        Position.z = -46.162f;
                    }
                }
                // Penyangga harta karun
                if (Position.z < 3.33803f)
                {
                    if ((Position.x > -1.0f && Position.x < 1.0f))
                    {
                        if (Position.z > 2.83803f)
                        {
                            Position.z = 2.83803f;
                        }
                        if (*flagHK == 0) 
                        {
                            if (direction == PICKITEM && Position.z > 2.53803f)
                            {
                                *flagHK = 2;
                            }
                        }
                    }
                }
                if (Position.z > 5.33803f)
                {
                    if ((Position.x > -1.0f && Position.x < 1.0f))
                    {
                        if (Position.z < 5.83803f)
                        {
                            Position.z = 5.83803f;
                        }
                        if (direction == PICKITEM && Position.z < 6.13803f)
                        {
                            *flagHK = 1;
                        }
                    }
                }
                if (Position.x < -1.0f) 
                {
                    if ((Position.z > 3.33803f && Position.z < 5.33803f))
                    {
                        if (Position.x > -1.3f)
                        {
                            Position.x = -1.3f;
                        }
                        if (direction == PICKITEM && Position.x > -1.6f)
                        {
                            *flagHK = 1;
                        }
                    }
                }
                if (Position.x > 1.0f)
                {
                    if ((Position.z > 3.33803f && Position.z < 5.33803f))
                    {
                        if (Position.x < 1.3f)
                        {
                            Position.x = 1.3f;
                        }
                        if (direction == PICKITEM && Position.x < 1.6f)
                        {
                            *flagHK = 1;
                        }
                    }
                }

                // Tetap berada di lantai
                if (*flag != 2 && (Position.x >= -5.0f && Position.x <= 5.0f) && (Position.z >= -52.162f && Position.z <= 9.33803f))
                {
                    Position.y = -0.92958f;
                }

                // Dinding belakang
                if (Position.z > 9.13803f)
                {
                    Position.z = 9.13803f;
                }
                // Dinding depan - kiri dan kanan
                if ((Position.x >= -5.0f && Position.x <= -3.0f) || (Position.x >= 3.0f && Position.x <= 5.0f))
                {
                    // Dinding kiri
                    if (Position.z > -46.662f)
                    {
                        if (Position.z < -46.162f)
                        {
                            Position.z = -46.162f;
                        }
                    }
                    // Dinding kanan
                    if (Position.z < -48.662f)
                    {
                        if (Position.z > -49.162f)
                        {
                            Position.z = -49.162f;
                        }
                    }
                }
                // Dinding depan - tengah
                if ((Position.x <= 3.0f && Position.x >= -3.0f) && (Position.z <= -46.662f && Position.z >= -48.662f))
                {
                    // Dinding tengah kiri
                    if (Position.x < -2.5f) 
                    {
                        Position.x = -2.5f;
                    }
                    // Dinding tengah kanan
                    if (Position.x > 2.5f) 
                    {
                        Position.x = 2.5f;
                    }
                }
                // Dinding depan - tengah atas
                if ((Position.x <= 3.0f && Position.x >= -3.0f) && Position.z < -46.162f && Position.y > 1.07042f)
                {
                    Position.z = -46.162f;
                }
                // Dinding kiri
                if (Position.x < -4.8f) 
                {
                    Position.x = -4.8f;
                }
                //Dinding kanan
                if (Position.x > 4.8f) 
                {
                    Position.x = 4.8f;
                }
            }
        }
        // Level 1
        if (Position.z < -48.662f && Position.z >= -106.662f)
        {
            if (*flagDoor < 4)
            {
                if (Position.z < -104.162f)
                {
                    Position.z = -104.162f;
                }
            }
            // Tidak menembus dinding parkour
            // Level 1 Parkour
            if (Position.x > 1.0f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.z <= -52.462f && Position.z >= -56.862f))
                {
                    if (Position.x <= 1.2f)
                    {
                        Position.x = 1.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -1.0f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.z <= -52.462f && Position.z >= -54.862f))
                {
                    if (Position.x >= -1.2f)
                    {
                        Position.x = -1.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z >= -54.662f && Position.z <= -52.662f)
            {
                if ((Position.x >= -7.0f && Position.x <= -1.0f) && (Position.y <= -0.92958f && Position.y >= -4.92958f))
                {
                    if (Position.z < -54.462f)
                    {
                        Position.z = -54.462f;
                    }
                    if (Position.z > -52.862f)
                    {
                        Position.z = -52.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z <= -52.662f && Position.z >= -60.662f)
            {
                if ((Position.x <= 7.0f && Position.x >= 1.0f) && (Position.y <= -0.92958f && Position.y >= -6.92958f))
                {
                    if (Position.z > -52.862f)
                    {
                        Position.z = -52.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z <= -56.662f && Position.z >= -60.662f)
            {
                if ((Position.x <= 1.0f && Position.x >= -5.0f) && (Position.y <= -0.92958f && Position.y >= -4.92958f))
                {
                    if (Position.z >= -57.162f)
                    {
                        Position.z = -57.162f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x >= -5.0f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.z <= -56.662f && Position.z >= -60.662f))
                {
                    if (Position.x < -4.8f)
                    {
                        Position.x = -4.8f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z >= -60.662f && Position.z <= -56.662f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.x >= -5.0f && Position.x <= 7.0f))
                {
                    if (Position.z < -60.162f)
                    {
                        Position.z = -60.162f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -62.662f && Position.z > -64.662f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.x >= -7.0f && Position.x <= 7.0f))
                {
                    if (Position.z > -62.862f)
                    {
                        Position.z = -62.862f;
                    }
                    *flag = 3;
                }
                // Level 2 Parkour
                    // Balok 1
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.x >= 2.0f && Position.x <= 6.0f))
                {
                    if (Position.z < -64.462f)
                    {
                        Position.z = -64.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -68.662f && Position.z > -69.662f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.x >= 2.0f && Position.x <= 6.0f))
                {
                    if (Position.z > -68.862f)
                    {
                        Position.z = -68.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < 2.0f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.z >= -68.662f && Position.z <= -64.662f))
                {
                    if (Position.x > 1.8f)
                    {
                        Position.x = 1.8f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 6.0f)
            {
                if ((Position.y <= -0.92958f && Position.y >= -4.92958f) && (Position.z >= -68.662f && Position.z <= -64.662f))
                {
                    if (Position.x < 6.2f)
                    {
                        Position.x = 6.2f;
                    }
                    *flag = 3;
                }
            }
            // Balok 2
            if (Position.z > -69.662f && Position.z < -68.662f)
            {
                if ((Position.x >= -1.0f && Position.x <= 3.0f) && (Position.y <= 0.92958f && Position.y >= -3.92958f))
                {
                    if (Position.z < -69.462f)
                    {
                        Position.z = -69.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -73.662f && Position.z > -74.662f)
            {
                if ((Position.x >= -1.0f && Position.x <= 3.0f) && (Position.y <= 0.92958f && Position.y >= -3.92958f))
                {
                    if (Position.z > -73.862f)
                    {
                        Position.z = -73.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 3.0f)
            {
                if ((Position.z >= -73.662f && Position.z <= -69.662f) && (Position.y <= 0.92958f && Position.y >= -3.92958f))
                {
                    if (Position.x < 3.2f)
                    {
                        Position.x = 3.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -1.0f)
            {
                if ((Position.z >= -73.662f && Position.z <= -69.662f) && (Position.y <= 0.92958f && Position.y >= -3.92958f))
                {
                    if (Position.x > -1.2f)
                    {
                        Position.x = -1.2f;
                    }
                    *flag = 3;
                }
            }
            //Balok 3
            if (Position.z < -73.662f && Position.z > -74.662f)
            {
                if ((Position.y <= 1.929578f && Position.y >= -2.92958f) && (Position.x <= 0.0f && Position.x >= -4.0f))
                {
                    if (Position.z < -74.462f)
                    {
                        Position.z = -74.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -78.662f && Position.z > -79.662f)
            {
                if ((Position.y <= 1.929578f && Position.y >= -2.92958f) && (Position.x <= 0.0f && Position.x >= -4.0f))
                {
                    if (Position.z > -78.862f)
                    {
                        Position.z = -78.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 0.0f)
            {
                if ((Position.y <= 1.929578f && Position.y >= -2.92958f) && (Position.z >= -78.662f && Position.z <= -74.662f))
                {
                    if (Position.x < 0.2f)
                    {
                        Position.x = 0.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -4.0f)
            {
                if ((Position.y <= 1.929578f && Position.y >= -2.92958f) && (Position.z >= -78.662f && Position.z <= -74.662f))
                {
                    if (Position.x > -4.2f)
                    {
                        Position.x = -4.2f;
                    }
                    *flag = 3;
                }
            }

            // Level 3 Parkour
            // Balok 1
            if (Position.z > -79.662f && Position.z < -78.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -79.462f)
                    {
                        Position.z = -79.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -81.662f && Position.z > -84.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -81.862f)
                    {
                        Position.z = -81.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > -4.0f)
            {
                if ((Position.z <= -79.662f && Position.z >= -81.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < -3.8f)
                    {
                        Position.x = -3.8f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -6.0f)
            {
                if ((Position.z <= -79.662f && Position.z >= -81.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > -6.2f)
                    {
                        Position.x = -6.2f;
                    }
                    *flag = 3;
                }
            }
            // Balok 2
            if (Position.z < -81.662f && Position.z > -84.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -84.462f)
                    {
                        Position.z = -84.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -86.662f && Position.z > -89.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -86.862f)
                    {
                        Position.z = -86.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > -4.0f)
            {
                if ((Position.z <= -84.662f && Position.z >= -86.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < -3.8f)
                    {
                        Position.x = -3.8f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -6.0f)
            {
                if ((Position.z <= -84.662f && Position.z >= -86.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > -6.2f)
                    {
                        Position.x = -6.2f;
                    }
                    *flag = 3;
                }
            }
            // Balok 3
            if (Position.z < -86.662f && Position.z > -89.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -89.462f)
                    {
                        Position.z = -89.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -91.662f && Position.z > -94.662f)
            {
                if ((Position.x >= -6.0f && Position.x <= -4.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -91.862f)
                    {
                        Position.z = -91.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > -4.0f && Position.x < -1.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < -3.8f)
                    {
                        Position.x = -3.8f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -6.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > -6.2f)
                    {
                        Position.x = -6.2f;
                    }
                    *flag = 3;
                }
            }
            // Balok 4
            if (Position.z < -86.662f && Position.z > -89.662f)
            {
                if ((Position.x >= -1.0f && Position.x <= 1.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -89.462f)
                    {
                        Position.z = -89.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -91.662f && Position.z > -94.662f)
            {
                if ((Position.x >= -1.0f && Position.x <= 1.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -91.862f)
                    {
                        Position.z = -91.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 1.0f && Position.x < 4.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < 1.2f)
                    {
                        Position.x = 1.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < -1.0f && Position.x > -4.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > -1.2f)
                    {
                        Position.x = -1.2f;
                    }
                    *flag = 3;
                }
            }
            // Balok 5
            if (Position.z < -86.662f && Position.z > -89.662f)
            {
                if ((Position.x >= 4.0f && Position.x <= 6.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -89.462f)
                    {
                        Position.z = -89.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -91.662f && Position.z > -94.662f)
            {
                if ((Position.x >= 4.0f && Position.x <= 6.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -91.862f)
                    {
                        Position.z = -91.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 6.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < 6.2f)
                    {
                        Position.x = 6.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < 4.0f && Position.x > 1.0f)
            {
                if ((Position.z <= -89.662f && Position.z >= -91.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > 3.8f)
                    {
                        Position.x = 3.8f;
                    }
                    *flag = 3;
                }
            }
            // Balok 6
            if (Position.z > -94.662f && Position.z < -91.662f)
            {
                if ((Position.x >= 4.0f && Position.x <= 6.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z < -94.462f)
                    {
                        Position.z = -94.462f;
                    }
                    *flag = 3;
                }
            }
            if (Position.z < -96.662f && Position.z > -98.662f)
            {
                if ((Position.x >= 4.0f && Position.x <= 6.0f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.z > -96.862f)
                    {
                        Position.z = -96.862f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x > 6.0f)
            {
                if ((Position.z <= -94.662f && Position.z >= -96.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x < 6.2f)
                    {
                        Position.x = 6.2f;
                    }
                    *flag = 3;
                }
            }
            if (Position.x < 4.0f)
            {
                if ((Position.z <= -94.662f && Position.z >= -96.662f) && (Position.y <= 1.929578f && Position.y >= -2.92958f))
                {
                    if (Position.x > 3.8f)
                    {
                        Position.x = 3.8f;
                    }
                    *flag = 3;
                }
            }

            // Tetap berada di lantai
            // Lantai belakang
            if (*flag != 2 && (Position.x <= 7.0f && Position.x >= -7.0f) && (Position.z <= -48.662f && Position.z >= -52.662f))
            {
                Position.y = -0.92958f;
            }
            // Lantai depan
            if (*flag != 2 && (Position.x <= 7.0f && Position.x >= -7.0f) && (Position.z >= -106.662f && Position.z <= -98.662f))
            {
                Position.y = -0.92958f;
            }

            // Lantai tengah (bagian parkour)
            // Level 1 Parkour
            // Balok 1
            if (Position.y > -3.92958f)
            {
                if (*flag != 2 && (Position.x >= -1.0f && Position.x <= 1.0f) && (Position.z <= -52.662f && Position.z >= -56.662f))
                {
                    Position.y = -0.92958f;
                }
                // Balok 2
                if (*flag != 2 && (Position.x <= -1.0f && Position.x >= -7.0f) && (Position.z <= -54.662f && Position.z >= -56.662f))
                {
                    Position.y = -0.92958f;
                }
                // Balok 3
                if (*flag != 2 && (Position.x <= -5.0f && Position.x >= -7.0f) && (Position.z <= -56.662f && Position.z >= -62.662f))
                {
                    Position.y = -0.92958f;
                }
                // Balok 4
                if (*flag != 2 && (Position.x <= 7.0f && Position.x >= -5.0f) && (Position.z <= -60.662f && Position.z >= -62.662f))
                {
                    Position.y = -0.92958f;
                }
            // Level 2 Parkour
                // Balok 1
                if (*flag != 2 && (Position.x <= 6.0f && Position.x >= 2.0f) && (Position.z <= -64.662f && Position.z >= -68.662f))
                {
                    Position.y = -0.92958f;
                }
            }
            if (Position.y > -1.92958f)
            {
                // Balok 2
                if (*flag != 2 && (Position.x <= 3.0f && Position.x >= -1.0f) && (Position.z <= -69.662f && Position.z >= -73.662f))
                {
                    Position.y = 0.92958f;
                }
            }
            if(Position.y > -0.929578f)
            {
                // Balok 3
                if (*flag != 2 && (Position.x <= 0.0f && Position.x >= -4.0f) && (Position.z <= -74.662f && Position.z >= -78.662f))
                {
                    Position.y = 1.929578f;
                }
            // Level 3 Parkour
                // Balok 1
                if (*flag != 2 && (Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -79.662f && Position.z >= -81.662f))
                {
                    Position.y = 1.929578f;
                }
                // Balok 2
                if (*flag != 2 && (Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -84.662f && Position.z >= -86.662f))
                {
                    Position.y = 1.929578f;
                }
                // Balok 3
                if (*flag != 2 && (Position.x <= -4.0f && Position.x >= -6.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    Position.y = 1.929578f;
                }
                // Balok 4
                if (*flag != 2 && (Position.x <= 1.0f && Position.x >= -1.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    Position.y = 1.929578f;
                }
                // Balok 5
                if (*flag != 2 && (Position.x <= 6.0f && Position.x >= 4.0f) && (Position.z <= -89.662f && Position.z >= -91.662f))
                {
                    Position.y = 1.929578f;
                }
                //Balok 6
                if (*flag != 2 && (Position.x <= 6.0f && Position.x >= 4.0f) && (Position.z <= -94.662f && Position.z >= -96.662f))
                {
                    Position.y = 1.929578f;
                }
            }

            // Tidak menembus dinding
            // Dinding belakang tengah - atas
            if ((Position.x <= 3.0f && Position.x >= -3.0f) && Position.z > -49.162f && Position.y > 1.07042f)
            {
                Position.z = -49.162f;
            }
            // Dinding depan & belakang - kiri & kanan
            if ((Position.x <= 7.0f && Position.x >= 3.0f) || (Position.x <= -3.0f && Position.x >= -7.0f))
            {
                // Dinding belakang
                if (Position.z > -49.162f)
                {
                    Position.z = -49.162f;
                }
                // Dinding depan
                if (Position.z < -104.162f)
                {
                    Position.z = -104.162f;
                }
            }
            // Dinding depan - tengah - kiri & kanan
            if ((Position.x <= 3.0f && Position.x >= -3.0f) && (Position.z <= -104.662f && Position.z >= -106.662f))
            {
                // Dinding tengah kiri
                if (Position.x < -2.5f)
                {
                    Position.x = -2.5f;
                }
                // Dinding tengah kanan
                if (Position.x > 2.5f)
                {
                    Position.x = 2.5f;
                }
            }
            // Dinding depan - tengah - atas
            if ((Position.x <= 3.0f && Position.x >= -3.0f) && Position.z < -104.162f && Position.y > 1.07042f)
            {
                Position.z = -104.162f;
            }
            // Dinding kiri
            if (Position.x < -6.8f) 
            {
                Position.x = -6.8f;
            }
            // Dinding kanan
            if (Position.x > 6.8f) 
            {
                Position.x = 6.8f;
            }
        }

        // Level 3
        if (Position.z < -106.662f)
        {
            // Masuk area winning
            if ((Position.z > -114.359f && Position.z < -108.359f) && (Position.x < 49.0054f && Position.x > 48.0054f))
            {
                *flagScreen = 3;
            }
            
            // Mekanik tidak menembus pintu
            if (*button1 == 0 || *button2 == 0 || *button3 == 0) 
            {
                if (Position.x > 44.5018f)
                {
                    Position.x = 44.5018f;
                }
            }

            if ((Position.x > 44.99f && Position.x < 48.983f) && (Position.z > -114.443f && Position.z < -108.374f))
            {
                if (Position.z < -113.943f)
                {
                    Position.z = -113.943f;
                }
                if (Position.z > -108.874f)
                {
                    Position.z = -108.874f;
                }
            }

            // Tidak bisa menembus lantai
            if (*flag != 2 && (Position.x < 49.0054f && Position.x > -31.0f) && (Position.z < -106.662f && Position.z > -164.431f))
            {
                Position.y = -0.92958f;
            }

            // Tidak Bisa menembus dinding
            if (Position.z < -106.662f)
            {
                if ((Position.x > 3.0f && Position.x < 44.9568f) || (Position.x < -3.0f && Position.x > -31.026f))
                {
                    if (Position.z > -107.162f) 
                    {
                        Position.z = -107.162f;
                    }
                }
            }
            if (Position.x > -31.0329f)
            {
                if (Position.x < -30.5329f)
                {
                    Position.x = -30.5329f;
                }
            }
            if (Position.z > -164.431f)
            {
                if (Position.z < -163.931f)
                {
                    Position.z = -163.931f;
                }
            }
            if (Position.x < 45.0047f)
            {
                if ((Position.z < -114.344 && Position.z > -164.351f) || (Position.z > -108.344f && Position.z < -106.344f))
                {
                    if (Position.x > 44.5047f)
                    {
                        Position.x = 44.5047f;
                    }
                }
            }
            if (Position.z > -116.439f && (Position.x > 24.9812f && Position.x < 44.9794f))
            {
                if (Position.z < -115.939f)
                {
                    Position.z = -115.939f;
                }
            }
            if (Position.x < 24.9812f && (Position.z < -116.472f && Position.z > -124.455f))
            {
                if (Position.x > 24.4812f)
                {
                    Position.x = 24.4812f;
                }
            }
            if (Position.z < -124.455f && (Position.x > 24.9831f && Position.x < 26.9831f))
            {
                if (Position.z > -123.955f)
                {
                    Position.z = -123.955f;
                }
            }
            if (Position.x > 26.9831f && (Position.z > -124.455f && Position.z < -118.455f))
            {
                if (Position.x < 27.4831f)
                {
                    Position.x = 27.4831f;
                }
            }
            if (Position.z < -118.471f && (Position.x > 26.9829f && Position.x < 44.9811f))
            {
                if (Position.z > -118.971f)
                {
                    Position.z = -118.971f;
                }
            }
            if (Position.z > -118.187f && (Position.x < 17.1729f && Position.x > -18.8338f))
            {
                if (Position.z < -117.687f)
                {
                    Position.z = -117.687f;
                }
            }
            if (Position.x < -18.8338f && (Position.z < -118.233f && Position.z > -156.232f))
            {
                if (Position.x > -19.3338f)
                {
                    Position.x = -19.3338f;
                }
            }
            if (Position.z < -156.232f && (Position.x > -18.8256f && Position.x < -6.85119f))
            {
                if (Position.z > -156.732f)
                {
                    Position.z = -156.732f;
                }
            }
            if (Position.x > -6.85119f && (Position.z > -156.216f && Position.z < -154.216f))
            {
                if (Position.x < -6.35119f)
                {
                    Position.x = -6.35119f;
                }
            }
            if (Position.z > -154.216f && (Position.x < -6.85289f && Position.x > -16.8512f))
            {
                if (Position.z < -153.716f)
                {
                    Position.z = -153.716f;
                }
            }
            if (Position.x > -16.8256f && (Position.z > -154.232f && Position.z < -120.232f))
            {
                if (Position.x < -16.3256f)
                {
                    Position.x = -16.3256f;
                }
            }
            if (Position.z < -120.231f && (Position.x > -16.8321f && Position.x < 15.1746f))
            {
                if (Position.z > -120.731f)
                {
                    Position.z = -120.731f;
                }
            }
            if (Position.x < 15.178f)
            {
                if (Position.z < -120.203f && Position.z > -126.203f) 
                {
                    if (Position.x > 14.678f)
                    {
                        Position.x = 14.678f;
                    }
                }
                if (Position.z < -128.203f && Position.z > -138.532f)
                {
                    if (Position.x > 14.678f)
                    {
                        Position.x = 14.678f;
                    }
                }
                if (Position.z < -140.532f && Position.z > -154.16f)
                {
                    if (Position.x > 14.678f)
                    {
                        Position.x = 14.678f;
                    }
                }
            }
            if (Position.x < 15.1527f && Position.x > 7.15274f)
            {
                if (Position.z > -126.28f)
                {
                    if (Position.z < -125.78f)
                    {
                        Position.z = -125.78f;
                    }
                }
                if (Position.z < -128.286f)
                {
                    if (Position.z > -128.786f)
                    {
                        Position.z = -128.786f;
                    }
                }
                if (Position.z > -138.532f)
                {
                    if (Position.z < -138.032f)
                    {
                        Position.z = -138.032f;
                    }
                }
                if (Position.z < -140.532f)
                {
                    if (Position.z > -141.032f)
                    {
                        Position.z = -141.032f;
                    }
                }
                if (Position.z > -154.16f)
                {
                    if (Position.z < -153.66f)
                    {
                        Position.z = -153.66f;
                    }
                }
            }
            if (Position.z < -156.16f && (Position.x < 17.1926f && Position.x > 7.18767f))
            {
                if (Position.z > -156.66f)
                {
                    Position.z = -156.66f;
                }
            }
            if (Position.x > 17.1926f && (Position.z > -156.21f && Position.z < -118.187f))
            {
                if (Position.x < 17.6926f)
                {
                    Position.x = 17.6926f;
                }
            }
            if (Position.x < 7.15274f)
            {
                if (Position.x > 6.65274f)
                {
                    if (Position.z < -126.286f && Position.z > -128.286f) 
                    {
                        Position.x = 6.65274f;
                    }
                    if (Position.z < -138.538f && Position.z > -140.538f)
                    {
                        Position.x = 6.65274f;
                    }
                    if (Position.z < -154.166f && Position.z > -156.166f)
                    {
                        Position.x = 6.65274f;
                    }
                }
            }
            if (Position.z < -131.965f && (Position.x > 17.2022f && Position.x < 35.2156f))
            {
                if (Position.z > -132.465f)
                {
                    Position.z = -132.465f;
                }
            }
            if (Position.x > 35.2156f && (Position.z > -131.935f && Position.z < -121.917f))
            {
                if (Position.x < 35.7156f)
                {
                    Position.x = 35.7156f;
                }
            }
            if (Position.z > -121.917f && (Position.x < 35.2157f && Position.x > 33.2157f))
            {
                if (Position.z < -121.417f)
                {
                    Position.z = -121.417f;
                }
            }
            if (Position.x < 33.2157f && (Position.z < -121.917f && Position.z > -129.917f))
            {
                if (Position.x > 32.7157f)
                {
                    Position.x = 32.7157f;
                }
            }
            if (Position.z > -129.937f && (Position.x < 33.2072f && Position.x > 17.2005f))
            {
                if (Position.z < -129.437f)
                {
                    Position.z = -129.437f;
                }
            }
            if (Position.z > -154.22f && (Position.x < 45.0003f && Position.x > 35.0003f))
            {
                if (Position.z < -153.72f)
                {
                    Position.z = -153.72f;
                }
            }
            if (Position.x > 35.2161f && (Position.z > -154.28f && Position.z < -138.273f))
            {
                if (Position.x < 35.7161f)
                {
                    Position.x = 35.7161f;
                }
            }
            if (Position.z > -138.273f && (Position.x < 35.2015f && Position.x > 33.2015f))
            {
                if (Position.z < -137.773f)
                {
                    Position.z = -137.773f;
                }
            }
            if (Position.x < 33.2015f && (Position.z < -138.273f && Position.z > -156.28f))
            {
                if (Position.x > 32.7015f)
                {
                    Position.x = 32.7015f;
                }
            }
            if (Position.z < -156.28f && (Position.x > 33.2161f && Position.x < 45.0019f))
            {
                if (Position.z > -156.78f)
                {
                    Position.z = -156.78f;
                }
            }
            if (Position.z > -164.355f && Position.z < -136.348f)
            {
                if (Position.x > 27.897f)
                {
                    if (Position.x < 28.397f)
                    {
                        Position.x = 28.397f;
                    }
                }
                if (Position.x < 25.897f)
                {
                    if (Position.x > 25.397f)
                    {
                        Position.x = 25.397f;
                    }
                }
            }
            if (Position.z > -136.348f && (Position.x > 25.897f && Position.x < 27.897f))
            {
                if (Position.z < -135.848f)
                {
                    Position.z = -135.848f;
                }
            }
            if (Position.x > 1.72883f && (Position.z > -164.138f && Position.z < -126.32f))
            {
                if (Position.x < 2.22883f)
                {
                    Position.x = 2.22883f;
                }
            }
            if (Position.x > 1.74395f && Position.x < 9.74395f)
            {
                if (Position.z > -132.347f)
                {
                    if (Position.z < -131.847f)
                    {
                        Position.z = -131.847f;
                    }
                }
                if (Position.z < -134.347f)
                {
                    if (Position.z > -134.847f)
                    {
                        Position.z = -134.847f;
                    }
                }
                if (Position.z > -144.387f)
                {
                    if (Position.z < -143.887f)
                    {
                        Position.z = -143.887f;
                    }
                }
                if (Position.z < -146.387f)
                {
                    if (Position.z > -146.887f)
                    {
                        Position.z = -146.887f;
                    }
                }
            }
            if (Position.x > 9.74564f)
            {
                if (Position.x < 10.24564f)
                {
                    if (Position.z > -134.347f && Position.z < -132.347f)
                    {
                        Position.x = 10.24564f;
                    }
                    if (Position.z > -146.387f && Position.z < -144.387f)
                    {
                        Position.x = 10.24564f;
                    }
                }
            }
            if (Position.z > -126.32f && (Position.x < 1.73399f && Position.x > -8.20889f))
            {
                if (Position.z < -125.82f)
                {
                    Position.z = -125.82f;
                }
            }
            if (Position.x < -8.20889f && (Position.z < -126.317f && Position.z > -148.325f))
            {
                if (Position.x > -8.70889f)
                {
                    Position.x = -8.70889f;
                }
            }
            if (Position.z < -148.325f && (Position.x > -8.20273f && Position.x < -6.20273f))
            {
                if (Position.z > -148.825f)
                {
                    Position.z = -148.825f;
                }
            }
            if (Position.x > -6.20273f && (Position.z > -148.325f && Position.z < -128.325f))
            {
                if (Position.x < -5.70273f)
                {
                    Position.x = -5.70273f;
                }
            }
            if (Position.z < -128.332f && (Position.x > -6.2072f && Position.x < -0.261208f))
            {
                if (Position.z > -128.832f)
                {
                    Position.z = -128.816f;
                }
            }
            if (Position.x < -0.271172f && (Position.z < -128.332f && Position.z > -164.138f))
            {
                if (Position.x > -0.771172f)
                {
                    Position.x = -0.771172f;
                }
            }
        }
        if (*button1 == 1 && *button2 == 1 && *button3 == 1) 
        {
            if (*flagSound == 7) 
            {
                *flagSound = 10;
            }
        }
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, int *flag, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif