cmake_minimum_required(VERSION 3.18)

project(SampleApp VERSION 0.0.1 LANGUAGES CSharp)

add_library(SampleApp SHARED 
		src/MapGenerator.cs
		src/Noise.cs
		src/Script.cs
		Properties/AssemblyInfo.cs
	)

target_link_libraries(SampleApp
    PUBLIC Farscape::ScriptCore
)

add_library(Farscape::SampleApp ALIAS SampleApp)