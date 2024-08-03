// ConexionBD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) { // Operador logico OR
        cout << "Conectado a la base de datos exitosamente." << endl;

        // Ejemplo de ejecución de una consulta
        SQLHSTMT hStmt; //Statement
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt); //
        cout << "+---------------------------------------------------------------------------------------------------------------------------------+" << endl;
        cout << "|No. Empleado " << "| Nombre " << "| Apellido Paterno " << "|Apellido Materno " << "| Fecha Nacimiento " << "|        RFC            " << "|      Centro Trabajo     |" << endl;
        // Ejemplo de consulta SELECT
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Datos_Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLCHAR name[50];
            SQLCHAR first_name[50];
            SQLCHAR last_name[50];
            SQLCHAR Fecha [15];
            SQLCHAR RFC[50];
            SQLCHAR Centro_Trabajo[50];

            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, first_name, sizeof(first_name), NULL);
                SQLGetData(hStmt, 4, SQL_C_CHAR, last_name, sizeof(last_name), NULL);
                SQLGetData(hStmt, 5, SQL_C_CHAR, Fecha, sizeof(Fecha), NULL);
                SQLGetData(hStmt, 6, SQL_C_CHAR, RFC, sizeof(RFC), NULL);
                SQLGetData(hStmt, 7, SQL_C_CHAR, Centro_Trabajo, sizeof(Centro_Trabajo), NULL);

                cout << "|     " << num_empleado << "         " << name << "         " << first_name << "          " << last_name << "           " << Fecha << "           " << RFC <<"           " << Centro_Trabajo << endl;
            }
        }

        // Liberar el manejador de conexion 
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


    }
    else {
        cout << "Fallo la conexion a la base de datos" << endl;
    }

    // Desconectar y liberar gestores de entorno
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}