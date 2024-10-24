// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#include "ig-aux.h"
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor())
   {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //

   if(dvao == nullptr)
   {
      DescrVBOAtribs *pos_dvbo = new DescrVBOAtribs(ind_atrib_posiciones, vertices);
      dvao = new DescrVAO(numero_atributos_cauce, pos_dvbo);

      DescrVBOInds *ind_dvbo = new DescrVBOInds(triangulos);
      dvao->agregar(ind_dvbo);

      if(col_ver.size() != 0)
      {
         DescrVBOAtribs *col_dvbo = new DescrVBOAtribs(ind_atrib_colores, col_ver);
         dvao->agregar(col_dvbo);
      }
      if(nor_ver.size() != 0)
      {
         DescrVBOAtribs *nor_dvbo = new DescrVBOAtribs(ind_atrib_normales, nor_ver);
         dvao->agregar(nor_dvbo);
      }
      if(cc_tt_ver.size() != 0)
      {
         DescrVBOAtribs *cc_tt_dvbo = new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver);
         dvao->agregar(cc_tt_dvbo);
      }
   }


   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'
   dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
   if(tieneColor())
   {
      cauce->popColor();
   }
}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   //    2. Dibujar la malla (únicamente visualizará los triángulos), se usa el método 'draw' del VAO (dvao)
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   // ....
   if(!col_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_colores, false);
   }
   if(!nor_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_normales, false);
   }
   if(!nor_tri.empty())
   {
      dvao->habilitarAtrib(ind_atrib_normales, false);
   }
   if(!cc_tt_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_coord_text, false);
   }

   dvao->draw(GL_TRIANGLES);

   if(!col_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_colores, true);
   }
   if(!nor_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_normales, true);
   }
   if(!nor_tri.empty())
   {
      dvao->habilitarAtrib(ind_atrib_normales, true);
   }
   if(!cc_tt_ver.empty())
   {
      dvao->habilitarAtrib(ind_atrib_coord_text, true);
   }
}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);


   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

CuboColores::CuboColores()
:  MallaInd("cubo 8 vertices con colores")
{
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   glm::vec<3, float> rgb_color;
   for (auto &vert : vertices) {
      rgb_color = {0.0, 0.0, 0.0};
      for (int i = 0; i < 3; i++) {
         if (vert[i] == -1.0)
         rgb_color[i] = 0.0;
         else if (vert[i] == 1.0)
         rgb_color[i] = 1.0;
      }
      col_ver.push_back(rgb_color);
   }


}

Tetraedro::Tetraedro(glm::vec3 color)
:  MallaInd("tetraedro 4 vértices")
{
   vertices = 
   {  { 0.0, 0.0, 1.0 }, // 0
      { 1.0, 0.0, 0.0 }, // 1
      { 0.0, 1.0, 0.0 }, // 2
      { 0.0, 0.0, 0.0 }, // 3
   } ;

   triangulos = 
   {  { 0, 1, 2 },
      { 0, 2, 3 },
      { 0, 3, 1 },
      { 1, 3, 2 },
   } ;

   ponerColor(color);

}

EstrellaZ::EstrellaZ(uint n)
:  MallaInd("estrella Z de N puntas")
{
   float radio_grande = 0.5;
   float radio_pequenio = radio_grande/2;
   glm::vec3 centro = {0.5, 0.5, 0.0};
   vertices.push_back(centro);
   col_ver.push_back({1.0, 1.0, 1.0});

   float angulo = 360.0/n;

   for(uint i=0; i<n; i++)
   {
      float x_grande = centro[0] + radio_grande*cos(glm::radians(angulo*i));
      float y_grande = centro[1] + radio_grande*sin(glm::radians(angulo*i));

      vertices.push_back({x_grande, y_grande, 0.0});
      col_ver.push_back({x_grande, y_grande, 0.0});

      float x_pequenio = centro[0] + radio_pequenio*cos(glm::radians(angulo*i + angulo/2));
      float y_pequenio = centro[1] + radio_pequenio*sin(glm::radians(angulo*i + angulo/2));

      vertices.push_back({x_pequenio, y_pequenio, 0.0});
      col_ver.push_back({x_pequenio, y_pequenio, 0.0});
   }

   uint aux1 = 1;
   uint aux2 = 2;

   for(uint i=0; i<2*n; i++)
   {
      triangulos.push_back({0, aux1, aux2});

      if(i%2 == 0)
      {
         aux1 += 2;
      }
      else
      {
         aux2 += 2;
      }

      if(aux1>=2*n)
      {
         aux1 = 1;
      }
   }
}

CasaX::CasaX()
:  MallaInd("Casa")
{
   vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, +0.75 }, // 1
         { 0.0, +0.75, 0.0 }, // 2
         { 0.0, +0.75, +0.75 }, // 3
         { +1.0, 0.0, 0.0 }, // 4
         { +1.0, 0.0, +0.75 }, // 5
         { +1.0, +0.75, 0.0 }, // 6
         { +1.0, +0.75, +0.75 }, // 7
         { +1.0, +1.0, +0.375}, // 8
         { 0.0, +1.0, +0.375}, // 9
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)
         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)
         {8,7,6}, {2,3,9},
         {2,6,8}, {2,9,8},
         {3,9,8}, {3,7,8},
      } ;

   for (auto &vert : vertices) {
      col_ver.push_back(vert);
   }

}

MallaTriangulo::MallaTriangulo()
:  MallaInd("Triangulo")
{
   vertices =
      {  { -0.5, 0.0, 0.0 }, // 0
         { +0.5, 0.0, 0.0 }, // 1
         { 0.0, sqrt(2), 0.0 }, // 2
      } ;

   triangulos =
      {  {0, 1, 2},
      } ;
}

MallaCuadrado::MallaCuadrado()
: MallaInd("Cuadrado") {

   vertices = {
      { -1.0, -1.0, 0.0 }, // 0
      { -1.0, +1.0, 0.0 }, // 1
      { +1.0, -1.0, 0.0 }, // 2
      { +1.0, +1.0, 0.0 }, // 3
   };

   triangulos = {
      {0, 1, 2},
      {1, 3, 2},
   };

}

MallaPiramide::MallaPiramide()
: MallaInd("Piramide")
{
   vertices = {
      { 0.0, 0.0, 0.0 }, // 0
      { +2.0, 0.0, 0.0 }, // 1
      { 0.0, 0.0, +2.0 }, // 2
      { +1.0, 0.0, +2.0 }, // 3
      { +1.0, 0.0, +1.0 }, // 4
      { +2.0, 0.0, +1.0 }, // 5
      { +1.0, 2.0, +1.0 }, // 6
   };

   triangulos = {
      {0, 1, 6},
      {1, 5, 6},
      {5, 6, 4},
      {6, 3, 4},
      {2, 3, 6},
      {0, 6, 2},
      {2, 3, 4},
      {1, 4, 5},
      {0, 1, 2},
   };
}

PiramideEstrellaZ::PiramideEstrellaZ(uint n)
:  MallaInd("Piramide estrella Z")
{
   float radio_grande = 0.5;
   float radio_pequenio = radio_grande/2;
   glm::vec3 centro = {0.5, 0.5, 0.0};
   vertices.push_back(centro);
   col_ver.push_back({1.0, 1.0, 1.0});

   float angulo = 360.0/n;

   for(uint i=0; i<n; i++)
   {
      float x_grande = centro[0] + radio_grande*cos(glm::radians(angulo*i));
      float y_grande = centro[1] + radio_grande*sin(glm::radians(angulo*i));

      vertices.push_back({x_grande, y_grande, 0.0});
      col_ver.push_back({x_grande, y_grande, 0.0});

      float x_pequenio = centro[0] + radio_pequenio*cos(glm::radians(angulo*i + angulo/2));
      float y_pequenio = centro[1] + radio_pequenio*sin(glm::radians(angulo*i + angulo/2));

      vertices.push_back({x_pequenio, y_pequenio, 0.0});
      col_ver.push_back({x_pequenio, y_pequenio, 0.0});
   }

   uint aux1 = 1;
   uint aux2 = 2;

   vertices.push_back({0.5, 0.5, 0.5});
   col_ver.push_back({1.0, 1.0, 1.0});

   for(uint i=0; i<2*n; i++)
   {
      triangulos.push_back({0, aux1, aux2});
      triangulos.push_back({vertices.size()-1, aux1, aux2});
      
      if(i%2 == 0)
      {
         aux1 += 2;
      }
      else
      {
         aux2 += 2;
      }

      if(aux1>=2*n)
      {
         aux1 = 1;
      }
   }

   // OTRA OPCION

   // float cordX_Central = 0.5;
   // float cordY_Central = 0.5;
   // float cordZ_Central = 0.5;
   // float radio = 0.5;

   // vertices.push_back({cordX_Central, cordY_Central, 0});
   // col_ver.push_back({1, 1, 1});

   // float x;
   // float y;
   // float x1;
   // float y1;

   // float angulo_ini = (360/n) * M_PI/180;
   // float angulo_ini_abajo = angulo_ini/2;
   // float angulo = 0;
   // float angulo_abajo = angulo_ini_abajo;

   // for(unsigned i = 0; i < n; i++){

   //    x1 = cordX_Central + (radio/2) * cos(angulo_abajo);
   //    y1 = cordY_Central + (radio/2) * sin(angulo_abajo);
   //    vertices.push_back({x1, y1, 0});
   //    col_ver.push_back({x1, y1, 0});
   //    angulo_abajo += angulo_ini;

   //    angulo += angulo_ini;
   //    x = cordX_Central + radio * cos(angulo);
   //    y = cordY_Central + radio * sin(angulo);
   //    vertices.push_back({x, y, 0});
   //    col_ver.push_back({x, y, 0});

      
   // }

   // vertices.push_back({cordX_Central,cordY_Central,cordZ_Central});

   // for (unsigned i = 1; i < 2*n; i++){

   //    triangulos.push_back({0,i,i+1});
   //    triangulos.push_back({0,i,2*n+1});

   // }
   
   // triangulos.push_back({0,1,2*n});
   // triangulos.push_back({0,2*n, 2*n+1});
}

RejillaY::RejillaY(uint n, uint m)
:  MallaInd("Rejilla")
{
   float incr_x = 1.0/(n-1);
   float incr_z = 1.0/(m-1);

   for(int i=0; i<n; i++)
   {
      for(int j=0; j<m; j++)
      {
         vertices.push_back({i*incr_x, 0.0, j*incr_z});
         col_ver.push_back({i*incr_x, 0.0, j*incr_z});
      }
   }

   for(int i=0; i<n-1; i++)
   {
      for(int j=0; j<m-1; j++)
      {
         triangulos.push_back({i*m+j, i*m+j+1, (i+1)*m+j});
         triangulos.push_back({i*m+j+1, (i+1)*m+j+1, (i+1)*m+j});
      }
   }
}

MallaTorre::MallaTorre(uint n)
:  MallaInd("Torre")
{
   float x_coord = 0.5;
   float z_coord = 0.5;

   for(int i=0; i<n; i++)
   {
      vertices.push_back({x_coord, i*1, z_coord});
      vertices.push_back({x_coord, i*1, -z_coord});
      vertices.push_back({-x_coord, i*1, -z_coord});
      vertices.push_back({-x_coord, i*1, z_coord});
      

      vertices.push_back({x_coord, (i*1)+1, z_coord});
      vertices.push_back({x_coord, (i*1)+1, -z_coord});
      vertices.push_back({-x_coord, (i*1)+1, -z_coord});
      vertices.push_back({-x_coord, (i*1)+1, z_coord});
   }

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < 4; j++) {
         glm::uvec3 t1, t2;
         if (j == 3) {
            t1 = {i * 8 + j, i * 8, i * 8 + 4 + j};
            t2 = {i * 8, i * 8 + 4 + j, i * 8 + 4};
         } else {
            t1 = {i * 8 + j, i * 8 + j + 1, i * 8 + 4 + j};
            t2 = {i * 8 + j + 1, i * 8 + 4 + j, i * 8 + 4 + j + 1};
         }
         triangulos.push_back(t1);
         triangulos.push_back(t2);
    }
  }

   
}

// -----------------------------------------------------------------------------------------------
