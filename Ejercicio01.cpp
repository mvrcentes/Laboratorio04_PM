#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

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

void *varCostReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    std::cout << ps->products[ps->id].getNombre() << ":\tQ" <<(ps->products[ps->id].calcularUtilidad()) << std::endl;
    double* res = (double*)malloc(sizeof(double));
    *res = ps->totalSold += ps->products[ps->id].getProductSales();
    return res;
    pthread_exit(NULL);
};

int main(){
    pthread_t tid;
    Parameters p;
    fflush(stdin);


    //Producto  nombre  | precio por unidad | costo por unidad | unidades vendidas | ventas totales | utilidad | ventas del mes | costo de varianza | utilidad del mes
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

    p.products[1] = Producto("White mocha", 32, 19, 400, 12800, 5120, 0, 0, 0);
    p.products[2] = Producto("Cafe americano 8onz", 22, 13.20, 1590, 34980, 13992, 0, 0, 0);
    p.products[3] = Producto("Latte 8onz", 24, 17.20, 200, 4800, 1360, 0, 0, 0);
    p.products[4] = Producto("Toffee Coffe", 500, 50, 50, 5000, 500, 0, 0, 0);
    p.products[5] = Producto("Cappuccino 8onz", 600, 60, 60, 6000, 600, 0, 0, 0);
    p.products[6] = Producto("Smore late", 700, 70, 70, 7000, 700, 0, 0, 0);
    p.products[7] = Producto("Cafe tostado molido", 800, 80, 80, 8000, 800, 0, 0, 0);

    printf ("\n ---------------------------------------------\n");
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
        pthread_create(&tid, NULL, varCostReport, ( void *)&p);
        pthread_join(tid, &thread_result_VarCost);
    }

    printf ("\n --------------------------------------------- \n");
    double tSold = *(double*) thread_result_Sold;
    // double tUtility = *(double*) thread_result_VarCost;
    // double tUtilityMonth = *(double*) thread_result_MonthUtility;

    free(thread_result_Sold);
    std::cout << "Total de venta: \t" << tSold << std::endl;

    // std::cout << "\nTotal de venta: \t" << tUtilityMonth << std::endl;


    pthread_exit(NULL);
}



