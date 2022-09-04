#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <iostream>
#include <iterator>
#include <list>


//Variables 
double totalSold, varCost, monthUtility;
#define TOTAL_PRODUCTS 8
void* thread_result_Sold;
void* thread_result_VarCost; 
void* thread_result_MonthUtility;

class Producto{  
  private:
    std::string nombre;
    double unitPrice, unitCost, unitSold, productSales, utility, soldAmountMonth, varCost, utilityMonth;
    
  public:
    Producto() {}

    Producto(std::string nombre, double unitPrice, double unitCost, double unitSold, double productSales, double utility, double soldAmountMonth, double varCost, double utilityMonth){
      this->nombre = nombre;
      this->unitPrice = unitPrice;
      this->unitCost = unitCost;
      this->unitSold = unitSold;
      this->productSales = productSales;
      this->utility = utility;
      this->soldAmountMonth = soldAmountMonth;
      this->varCost = varCost;
      this->utilityMonth = utilityMonth;
    }

    //getters and setters
    std::string getNombre(){
      return nombre;
    }
    void setNombre(std::string nombre){
      this->nombre = nombre;
    }
    double getUnitPrice(){
      return unitPrice;
    }
    void setUnitPrice(double unitPrice){
      this->unitPrice = unitPrice;
    }
    double getUnitCost(){
      return unitCost;
    }
    void setUnitCost(double unitCost){
      this->unitCost = unitCost;
    }
    double getUnitSold(){
      return unitSold;
    }
    void setUnitSold(double unitSold){
      this->unitSold = unitSold;
    }
    double getProductSales(){
      return productSales;
    }
    void setProductSales(double productSales){
      this->productSales = productSales;
    }
    double getUtility(){
      return utility;
    }
    void setUtility(double utility){
      this->utility = utility;
    }
    double getSoldAmountMonth(){
      return soldAmountMonth;
    }
    void setSoldAmountMonth(double soldAmountMonth){
      this->soldAmountMonth = soldAmountMonth;
    }
    double getVarCost(){
      return varCost;
    }
    void setVarCost(double varCost){
      this->varCost = varCost;
    }
    double getUtilityMonth(){
      return utilityMonth;
    }
    void setUtilityMonth(double utilityMonth){
      this->utilityMonth = utilityMonth;
    }

    //funciones
    double ventasPorProducto(){
        return unitSold * unitPrice;
    }
    double calcularUtilidad(){
      return productSales - (unitSold * unitCost);
    }

};

struct Parameters{
  int id;
  double totalSold, varCost, monthUtility;
  Producto products[TOTAL_PRODUCTS];
//   std::list<std::list<Producto> > nested_list;
};

void *soldReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;
    std::cout << ps->products[ps->id].getNombre() << ":\tQ" << (ps->products[ps->id].ventasPorProducto()) << std::endl;

    double* res = (double*)malloc(sizeof(double));
    *res = ps->totalSold += ps->products[ps->id].getProductSales();
    return res;
    pthread_exit(NULL);
};

void *varUtilityReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    std::cout << ps->products[ps->id].getNombre() << ":\tQ" <<(ps->products[ps->id].calcularUtilidad()) << std::endl;
    double* res = (double*)malloc(sizeof(double));
    *res = ps->monthUtility += ps->products[ps->id].getProductSales();
    return res;
    pthread_exit(NULL);
};

void *varCostReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    // std::cout << ps->products[ps->id].getNombre() << ":\tQ" <<(ps->products[ps->id].calcularUtilidad()) << std::endl;
    double* res = (double*)malloc(sizeof(double));
    *res = ps->varCost += ps->products[ps->id].getVarCost();
    return res;
    pthread_exit(NULL);
};

int main(){
    pthread_t tid;
    Parameters p;
    fflush(stdin);
    int mes;

    

    //Producto  nombre  | precio por unidad | costo por unidad | unidades vendidas | ventas totales | utilidad | ventas del mes | costo de varianza | utilidad del mes

    double tSold;
    double tVarCost;
    double tUtilityMonth; 
    bool salir = false;
    
    while (!salir){
        std::cout << "Ingrese el mes: \n[1]\tJulio\n[2]\tAgosto\n";
        std::cin >> mes;

        switch(mes){
            case 1:
                p.products[0] = Producto(
                        "Porcion pastel de chocolate", //nombre
                        60, //precio por unidad
                        20, //costo por unidad
                        300, //unidades vendidas
                        18000, //ventas totales
                        12000, //utilidad
                        0, //ventas del mes
                        0, //costo de varianza
                        0); //utilidad del mes

                p.products[1] = Producto("White mocha", 32, 19.20, 400, 12800, 5120, 0, 0, 0);
                p.products[2] = Producto("Cafe americano 8onz", 22, 13.20, 1590, 34980, 13992, 0, 0, 0);
                p.products[3] = Producto("Latte 8onz", 24, 17.20, 200, 4800, 1360, 0, 0, 0);
                p.products[4] = Producto("Toffee Coffe", 28, 20.10, 390, 10920, 3081, 0, 0, 0);
                p.products[5] = Producto("Cappuccino 8onz", 24, 17.20, 1455, 34920, 25600, 0, 0, 0);
                p.products[6] = Producto("Smore late", 32, 23, 800, 25600, 7200, 0, 0, 0);
                p.products[7] = Producto("Cafe tostado molido", 60, 20, 60, 3600, 2400, 0, 0, 0);

                printf ("\n ---------------------------------------------\n");
                printf ("\n Reporte del mes de Julio\n");

                printf ("Ventas por producto \n\n");
                for (double i=0; i < TOTAL_PRODUCTS; i++){
                    p.id = i;
                    // std::cout << i << ": " << p.products[i].getNombre() << std::endl;
                    pthread_create(&tid, NULL, soldReport, ( void *)&p);
                    pthread_join(tid, &thread_result_Sold);
                }

                printf ("\n --------------------------------------------- \n");
                printf ("Utilidad por producto \n\n");
                for (double k=0; k < TOTAL_PRODUCTS; k++){
                    p.id = k;
                    pthread_create(&tid, NULL, varUtilityReport, ( void *)&p);
                    pthread_join(tid, &thread_result_MonthUtility);

                    pthread_create(&tid, NULL, varCostReport, ( void *)&p);
                    pthread_join(tid, &thread_result_VarCost);

                }

                printf ("\n --------------------------------------------- \n");

                tSold = *(double*) thread_result_Sold;
                tVarCost = *(double*) thread_result_VarCost;
                tUtilityMonth= *(double*) thread_result_MonthUtility;

                free(thread_result_Sold);
                std::cout << "Total de venta: \t" << tSold << std::endl;
                std::cout << "Total de costos variables: \t" << tVarCost << std::endl;
                std::cout << "Total de utilidad: \t" << tUtilityMonth << std::endl;
                printf ("\n --------------------------------------------- \n\n\n\n");

                p.totalSold = 0;
                p.varCost = 0;
                p.monthUtility = 0;
                break;
            case 2:
                p.products[1] = Producto("Porcion de pastel", 60, 20, 250, 15000, 10000, 0, 0, 0);
                p.products[1] = Producto("White mocha", 32, 19.20, 380, 12160, 4864, 0, 0, 0);
                p.products[2] = Producto("Cafe americano 8onz", 22, 13.20, 800, 17600, 7040, 0, 0, 0);
                p.products[3] = Producto("Latte 8onz", 24, 17.20, 250, 6000, 1700, 0, 0, 0);
                p.products[4] = Producto("Toffee Coffe", 28, 20.10, 600, 16800, 4740, 0, 0, 0);
                p.products[5] = Producto("Cappuccino 8onz", 24, 17.20, 1200, 28800, 8160, 0, 0, 0);
                p.products[6] = Producto("Smore late", 32, 23, 1540, 49280, 13860, 0, 0, 0);
                p.products[7] = Producto("Cafe tostado molido", 60, 20, 15, 900, 600, 0, 0, 0);


                printf ("\n ---------------------------------------------\n");
                printf ("\n Reporte del mes de Agosto\n");

                printf ("Ventas por producto \n\n");
                for (double i=0; i < TOTAL_PRODUCTS; i++){
                    p.id = i;
                    // std::cout << i << ": " << p.products[i].getNombre() << std::endl;
                    pthread_create(&tid, NULL, soldReport, ( void *)&p);
                    pthread_join(tid, &thread_result_Sold);
                }

                printf ("\n --------------------------------------------- \n");
                printf ("Utilidad por producto \n\n");
                for (double k=0; k < TOTAL_PRODUCTS; k++){
                    p.id = k;
                    pthread_create(&tid, NULL, varUtilityReport, ( void *)&p);
                    pthread_join(tid, &thread_result_MonthUtility);

                    pthread_create(&tid, NULL, varCostReport, ( void *)&p);
                    pthread_join(tid, &thread_result_VarCost);

                }

                printf ("\n --------------------------------------------- \n");
                
                tSold = *(double*) thread_result_Sold;
                tVarCost = *(double*) thread_result_VarCost;
                tUtilityMonth= *(double*) thread_result_MonthUtility;

                free(thread_result_Sold);
                std::cout << "Total de venta: \t" << tSold << std::endl;
                std::cout << "Total de costos variables: \t" << tVarCost << std::endl;
                std::cout << "Total de utilidad: \t" << tUtilityMonth << std::endl;
                printf ("\n --------------------------------------------- \n\n\n\n");

                p.totalSold = 0;
                p.varCost = 0;
                p.monthUtility = 0;      
                break;
                case 3:
                    salir = true;
            default:
                std::cout << "Mes no valido";
                break;
    }

    }

    pthread_exit(NULL);
}



