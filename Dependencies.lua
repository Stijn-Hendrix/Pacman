IncludeDir = {}

IncludeDir["stb_image"] = "%{wks.location}/Pacman/vendor/stb_image"
IncludeDir["GLFW"] = "%{wks.location}/Pacman/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/Pacman/vendor/Glad/include"
IncludeDir["glm"] = "%{wks.location}/Pacman/vendor/glm"

Library = {}

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"