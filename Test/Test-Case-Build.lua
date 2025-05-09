project "Test"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++20"

    staticruntime "off"

    externalwarnings "off"

    flags {}

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    defines {
        "SPDLOG_COMPILED_LIB",
        "_CRT_SECURE_NO_WARNINGS",
        "CORE_GUI_BUILD",
        "GLFW_INCLUDE_NONE",
        "IMGUI_DEFINE_MATH_OPERATORS",
        "ENABLE_ASSERTS",
    }

    files {
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs {
        "src",
        "%{wks.location}/Core/src",
        "%{wks.location}/Core/vendor",
    }

    externalincludedirs {
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.ImGui}",
    }

    links {
        "Core",
    }

    filter "system:windows"
        systemversion "latest"

    -- Define a custom build rule for copying files from AI/src/Puzzle to Test/src/cache
    prebuildcommands {
        "{COPY} %{wks.location}/AI/src/Puzzle/*.hpp %{wks.location}/Test/src/cache",
        "{COPY} %{wks.location}/AI/src/Puzzle/*.cpp %{wks.location}/Test/src/cache"
    }

    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "CORE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CORE_RELEASE"
        runtime "Release"
        symbols "on"
        optimize "speed"

    filter "configurations:Dist"
        defines "CORE_DIST"
        runtime "Release"
        symbols "off"
        optimize "speed"
