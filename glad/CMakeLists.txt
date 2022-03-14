project(glad)

add_library(glad src/glad.c include/glad/glad.h include/KHR/khrplatform.h ../stb/stb_image.h)
