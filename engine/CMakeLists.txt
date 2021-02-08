cmake_minimum_required(VERSION 3.12)

add_library(Farscape SHARED 
	src/test.cpp
	src/test.h
)

add_library(Farscape::Engine ALIAS Farscape)