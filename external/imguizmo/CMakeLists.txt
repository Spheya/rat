add_library(imguizmo STATIC 
	"src/GraphEditor.cpp"
	"src/ImCurveEdit.cpp"
	"src/ImGradient.cpp"
	"src/ImGuizmo.cpp"
	"src/ImSequencer.cpp"
)
target_include_directories(imguizmo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(imguizmo PUBLIC imgui)
