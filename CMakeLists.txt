cmake_minimum_required(VERSION 3.24)
project(untitled)
set(CMAKE_CXX_STANDARD 17)

# Download freeglut library and extract inside the project directory
# It should look like:
# freeglut/
#   bin/
#   include/
#   lib/

# Then you need to include header files such sa GL/glut.h
# The below line includes these header files
include_directories(freeglut/include) # freeglut/include has to contain the required OpenGL's .h files
# The below line links freeglut library
link_directories(freeglut/lib) # freeglut/lib has to contain the required OpenGL's .a files
# It will set library names to variable named OpenGlLibs
set(OpenGlLibs glu32 opengl32 freeglut)  # link libraises and NOTE: here we are linking freeglut instead glut


add_executable(untitled main.cpp App/WebServices/Client.h App/WebServices/ConnectionManager.h App/WebServices/Server.h App/WebServices/TcpInterface.h App/WebServices/OnlineGameController.h App/Game/GameModel.h App/Game/GameViewer.h App/Game/GameController.h App/BoardConfigurator/BoardConfiguratorController.h App/BoardConfigurator/BoardConfiguratorModel.h App/BoardConfigurator/BoardConfiguratorViewer.h App/AppViewer.h App/AppController.h App/Event/EventType.h App/Event/Event.h App/Event/EventHandler.h App/Menu/MenuController.h App/Menu/MenuViewer.h App/AppModel.h Screen.h App/GameElements/Board.h App/GameElements/Field.h App/GameElements/FieldViewer.h App/GameElements/ShipPlacerController.h App/GameElements/Coordinate.h App/GameElements/ShipContainerController.h App/GameElements/Ships/ShipFactory.h App/GameElements/Ships/AircraftCarrier.h App/GameElements/Ships/Battleship.h App/GameElements/Ships/Cruiser.h App/GameElements/Ships/Frigate.h App/GameElements/Ships/ShipViewer.h App/GameElements/ShipContainerViewer.h App/Utilities/Message.h App/Utilities/InputViewer.h App/Utilities/MessageViewer.h App/Utilities/Input.h App/WebServices/Response.h App/SceneViewer.h App/SceneController.h)

target_link_libraries(untitled ws2_32)
# Link freeglut library to the source program
target_link_libraries(untitled ${OpenGlLibs})