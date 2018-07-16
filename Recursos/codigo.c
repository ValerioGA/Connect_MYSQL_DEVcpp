#include<iostream>
#include<mysql.h>
#include<mysql_error.h>
#include<locale.h>
/*Un CRUD es:
	CREATE	: CREAR REGISTROS
	READ	: LEER REGISTROS 
	UPDATE	: MODIFICAR REGISTRO (UPDATE O ACTUALIZAR)
	DELETE	: ELIMINAR REGISTROS 
 */
using namespace std;
	class conne{
		
		public:
		MYSQL *obj;
		
		char* conectar(char *server, char *user, char *pw, char *database){
			
				if(!(obj=mysql_init(0)))
					{
						return "Error Create Objeto";
					}
					if(!mysql_real_connect(obj,server,user,pw,database,3306,NULL,0))
					{
						return (char*)mysql_error(obj);
					}else
					{
						return "++++++++ Base de Datos en Uso ++++++++";
					}
		}
		
		void desconectar(){
			mysql_close(obj);
		}
	};
	
	conne conexion;
	
	struct stalumno{
	char id[6];
	char nombre[20];
	char paterno[20];
	}alu;
	
	class clalumno{
		public:
			char *resultado;
			void insertar(struct stalumno x){
				try{
				conexion.conectar("localhost","root","","angela");
				char *consulta;
				char sentencia[]="INSERT INTO ALUMNO (ID,NOMBRE,PATERNO) VALUES (\'%s\',\'%s\',\'%s\')";
				consulta=new char[strlen(sentencia)+sizeof(stalumno)]-sizeof(int);
				sprintf(consulta,sentencia,alu.id,alu.nombre,alu.paterno);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj);
				}
				resultado="Registro Ingresado Correctamente\n";
				}catch(const char* msg){
					cout<<msg;
					conexion.desconectar();
				}
			}
			
			void modificar(struct stalumno x){
				try{
				conexion.conectar("localhost","root","","angela");
				char *consulta;
				char sentencia[]="UPDATE ALUMNO SET NOMBRE=\'%s\',PATERNO=\'%s\' wHERE ID=\'%s\'";
				consulta=new char[strlen(sentencia)+sizeof(stalumno)]-sizeof(int);
				sprintf(consulta,sentencia,alu.nombre,alu.paterno,alu.id);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj);
				}
				resultado="Registro Modificado\n";
				}catch(const char* msg){
					cout<<msg;
					conexion.desconectar();
				}
			}
			
			void eliminar(struct stalumno x){
				try{
				conexion.conectar("localhost","root","","angela");
				char *consulta;
				char sentencia[]="DELETE from ALUMNO WHERE ID=\'%s\'";
				consulta=new char[strlen(sentencia)+sizeof(stalumno)]-sizeof(int);
				sprintf(consulta,sentencia,alu.id);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj);
				}
				resultado="Registro ELiminado Correctamente\n";
				}catch(const char* msg){
					cout<<msg;
					conexion.desconectar();
				}
			}
			
			void mostrar(){//Esta es Otra Forma en un solo metodo
				   MYSQL           *objDatos;
				   MYSQL_RES       *res;
				   MYSQL_ROW        row;
				   MYSQL_FIELD     *columna;
				   int              i, j, k, l;
				   unsigned long   *lon;
				   MYSQL_ROW_OFFSET pos;
				   if(!(objDatos = mysql_init(0))) {
				      cout<<"Error Objeto"<<endl;
				      rewind(stdin);
				      getchar();	      
					}
				   if(!mysql_real_connect(objDatos,"localhost", "root", "", "angela", 3306, NULL, 0)) {
				      cout<<"Error BD"<<MYSQL_PORT<<" Error: "<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				   if(mysql_select_db(objDatos, "angela")) {
				      cout<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				   if(mysql_query(objDatos, "SELECT * FROM ALUMNO")) {
				      cout<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				if((res=mysql_store_result(objDatos))){
					i=(int)mysql_num_rows(res);
					j=(int)mysql_num_fields(res);
					cout<<endl<<"		Datos de Todos Los Alumnos"<<endl;
					l=1;
					for(l=0;l<i;l++){
						row=mysql_fetch_row(res);
						lon=mysql_fetch_lengths(res);
						cout<<endl;
						for(k=0;k<j;k++){
						cout<<"	"<<((row[k]==NULL)?"NULL":row[k])<<"	";
					}
				}cout<<endl;
			    mysql_free_result(res);
			   }
			   mysql_close(objDatos);
			   rewind(stdin);
			   cout<<endl;
			}
			
	};
	
	void salir(){
		cout<<"Programa Finalizado\n";
	}
	
	void menu(){
		int opcion;
		clalumno op;
		cout<<"Presentado por: Angela Flores\n";
		do{
		cout<<"*************************************************************\n";
		cout<<"                  +------------------------+"<<endl;
		cout<<"                  |          Menu          |"<<endl;
		cout<<"                  +------------------------+"<<endl;
		cout<<"                  | Seleccione una Opción  |"<<endl;
		cout<<"                  | 1.- Crear Registros    |"<<endl;
		cout<<"                  | 2.- Eliminar Registros |"<<endl;
		cout<<"                  | 3.- Modificar Registros|"<<endl;
		cout<<"                  | 4.- Ver Registros      |"<<endl;
		cout<<"                  | 5.- Salir              |"<<endl;
		cout<<"                  +------------------------+"<<endl;
		cout<<"*************************************************************"<<endl;
		
		clalumno x;
		cin>>opcion;
		
		switch(opcion){
				case 1:		
					cout<<"Ingrese Datos de Alumnos \n";
					cout<<"Ingrese ID : ";
					cin>>alu.id;
					cout<<"Ingrese Nombre: ";
					cin>>alu.nombre;
					cout<<"Ingrese Apellido Paterno: ";
					cin>>alu.paterno;
					op.insertar(alu);
					cout<<op.resultado;
				break;
				
				case 2:		
					clalumno op;
					cout<<"Ingrese Código de Alumno a Eliminar: ";
					cin>>alu.id;
					op.eliminar(alu);
					cout<<op.resultado;
				break;
				
				case 3:
					cout<<"Modificar Datos de Alumno\n";
					cout<<"Ingrese ID : ";
					cin>>alu.id;
					cout<<"\nModificará Registros del Alumno con ID "<<alu.id<<endl;
					cout<<"\nIngrese Nuevo Nombre: ";
					cin>>alu.nombre;
					cout<<"Ingrese Nuevo Apellido Paterno: ";
					cin>>alu.paterno;
					op.modificar(alu);
					cout<<op.resultado;
				break;
				
				case 4:
					op.mostrar();
					
				break;
				case 5: salir();
				break;
				default:
				cout<<"Opción Incorrecta\n";	
		}
	}while(opcion!=5);
	}
	
int main() {
	setlocale(LC_CTYPE,"Spanish");
	menu();
	return 0;
}
