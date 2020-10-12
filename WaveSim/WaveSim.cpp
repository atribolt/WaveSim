#include <GL/freeglut.h>
#include <iostream>
#include <functional>
#include <map>
#include <vector>

namespace Mouse {
  enum class Button {
    Left = GLUT_LEFT_BUTTON,
    Right = GLUT_RIGHT_BUTTON,
    Middle = GLUT_MIDDLE_BUTTON
  };

  namespace Callback {
    using Up = void (*)(Button, int, int);
    using Down = void (*)(Button, int, int);
  }
}

namespace Types {
  struct Dot {
    GLfloat _x;
    GLfloat _y;
  };

  struct Point {
    Dot _pos;
    GLfloat _weight;
  };

  // Read flat array as row from 2d grid
  struct Row {
    Point* _begin { nullptr };

    Point& operator[](size_t column) { 
      return _begin[column]; 
    }
    const Point& operator[](size_t column) const { 
      return _begin[column]; 
    }
  };

  // Read flat array as column from 2d grid
  template<size_t columns>
    struct Column {
      Point* _begin { nullptr };

      Point& operator[](size_t row) {
        return _begin[row * columns];
      }
      const Point& operator[](size_t row) const {
        return _begin[row * columns];
      }
    };

  // Mapping flat float array to 2d grid
  template<size_t columns>
    struct Grid {
      GLfloat* _begin { nullptr };

      Row getRow(size_t index) {
        return Row { _begin + (index * columns) };
      }

      Column<columns> getColumn(size_t index) {
        return Column<columns> { _begin + index };
      }
    };
}

namespace ProgramVariables {
  using MouseUpHandler = std::vector<Mouse::Callback::Up>;
  using MouseDownHandler = std::vector<Mouse::Callback::Down>;

  std::map<Mouse::Button, MouseUpHandler> mouseUpHandlers;
  std::map<Mouse::Button, MouseDownHandler> mouseDownHandlers;

  // c_ - count
  const GLuint c_axis = 3; // x, y, weight
  const GLuint c_vertices_X = 500; // density X axis
  const GLuint c_vertices_Y = 500; // density Y axis
  GLfloat grid[c_axis * c_vertices_X * c_vertices_Y] { 0.f }; 
}

void drawFunc();
void mouseFunc(int btn, int state, int x, int y);
void initMouseHandlers();

int main(int argc, char **argv)
{
  glutInit ( &argc, argv );
  glutInitContextVersion( 3, 3 );
  glutInitContextProfile ( GLUT_CORE_PROFILE );
  glutInitContextFlags ( GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG );

  glutInitWindowPosition ( 0, 0 );
  glutInitWindowSize ( 500, 500 );

  glClearColor( 1, 0, 0, 0 );
  glViewport( 0, 0, 500, 500 );
  
  glutCreateWindow ( "WaveSimulation" );

  glutDisplayFunc ( drawFunc );
  glutMouseFunc ( mouseFunc );

  glutMainLoop();

  return 0;
}

void drawFunc() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  glutSwapBuffers();
}

void mouseFunc(int btn, int state, int x, int y) {
  Mouse::Button button = Mouse::Button(btn);
  
  switch(state) {
    case GLUT_UP: {
      for(auto& mouseHandler : ProgramVariables::mouseUpHandlers[button])
        mouseHandler(button, x, y);
      
      break;
    }
    case GLUT_DOWN: {
      for(auto& mouseHandler : ProgramVariables::mouseDownHandlers[button])
        mouseHandler(button, x, y);
      
      break;
    }

    default: break;
  }
}

void initMouseHandlers() {
  auto leftClick = [](Mouse::Button button, int x, int y) {
    switch(button) {
      case Mouse::Button::Left:
      {
        
      }
    }
  };
}
