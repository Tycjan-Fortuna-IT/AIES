include "./solution_items.lua"

workspace "AI"
    architecture "x64"
    startproject "AI"

    configurations {
        "Debug",
        "Release",
        "Dist",
    }

    solution_items {
		".editorconfig"
	}

    flags {
        "MultiProcessorCompile",
    }

    filter "system:linux"
        toolset "clang"

    -- Folder name containing compiled output in a following format: /[config]-[platform]-[architecture]/.
    -- e.g. folder Debug-Windows-x64
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- List of directories leading to already compiled libraries that are in use
    LibDir = {}

    LibDir["SPDLOG"] = "%{wks.location}/Core/vendor/SPDLOG/" .. outputdir .. "/spdlog/spdlog.lib"
    LibDir["GLAD"] = "%{wks.location}/Core/vendor/GLAD/" .. outputdir .. "/GLAD/glad.lib"
    LibDir["GLFW"] = "%{wks.location}/Core/vendor/GLFW/" .. outputdir .. "/GLFW/glfw3.lib"
    LibDir["ImGui"] = "%{wks.location}/Core/vendor/ImGui/" .. outputdir .. "/ImGui/imgui.lib"

    -- List of directories leading to headers of the libraries in use
    IncludeDir = {}

    IncludeDir["SPDLOG"] = "%{wks.location}/Core/vendor/SPDLOG/include"
    IncludeDir["GLFW"] = "%{wks.location}/Core/vendor/GLFW/include"
    IncludeDir["GLAD"] = "%{wks.location}/Core/vendor/GLAD/include"
    IncludeDir["ImGui"] = "%{wks.location}/Core/vendor/ImGui"
    IncludeDir["GLM"] = "%{wks.location}/Core/vendor/GLM"
    IncludeDir["Icons"] = "%{wks.location}/Core/vendor/icons/include"

    include "Core/Core-Build-GUI.lua"
    include "AI/Client-Build-GUI.lua"
