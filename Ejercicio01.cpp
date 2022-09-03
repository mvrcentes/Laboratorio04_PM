#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


class Producto{  
  private:
    std::string nombre;
    int unitPrice, unitCost, unitSold, productSales, utility, soldAmountMonth, varCost, utilityMonth; 
    
  public:
    Producto(std::string nombre, int unitPrice, int unitCost, int unitSold, int productSales, int utility, int soldAmountMonth, int varCost, int utilityMonth){
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
    int getUnitPrice(){
      return unitPrice;
    }
    void setUnitPrice(int unitPrice){
      this->unitPrice = unitPrice;
    }
    int getUnitCost(){
      return unitCost;
    }
    void setUnitCost(int unitCost){
      this->unitCost = unitCost;
    }
    int getUnitSold(){
      return unitSold;
    }
    void setUnitSold(int unitSold){
      this->unitSold = unitSold;
    }
    int getProductSales(){
      return productSales;
    }
    void setProductSales(int productSales){
      this->productSales = productSales;
    }
    int getUtility(){
      return utility;
    }
    void setUtility(int utility){
      this->utility = utility;
    }
    int getSoldAmountMonth(){
      return soldAmountMonth;
    }
    void setSoldAmountMonth(int soldAmountMonth){
      this->soldAmountMonth = soldAmountMonth;
    }
    int getVarCost(){
      return varCost;
    }
    void setVarCost(int varCost){
      this->varCost = varCost;
    }
    int getUtilityMonth(){
      return utilityMonth;
    }
    void setUtilityMonth(int utilityMonth){
      this->utilityMonth = utilityMonth;
    }
};

struct Parameters{
  int id, amount, totalSold, varCost, monthUtility;
  Producto products[];
};

void *soldReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    int sum;
    // std::string* txt = ps->products[ps->id].getNombre() + ": "  (ps->products[ps->id].getProductSales());
    return ps->products[ps->id].getNombre();
};

int main(){
    pthread_t tid;
    Parameters *p;

    p->products[0] = Producto("Leche", 100, 10, 10, 100, 10, 10, 10, 10);
    p->products[1] = Producto("Producto 2", 200, 20, 20, 2000, 200, 200, 20, 20);
    p->products[2] = Producto("Producto 3", 300, 30, 30, 3000, 300, 300, 30, 30);
    p->products[3] = Producto("Producto 4", 400, 40, 40, 4000, 400, 400, 40, 40);
    p->products[4] = Producto("Producto 5", 500, 50, 50, 5000, 500, 500, 50, 50);
    p->products[5] = Producto("Producto 6", 600, 60, 60, 6000, 600, 600, 60, 60);
    p->products[6] = Producto("Producto 7", 700, 70, 70, 7000, 700, 700, 70, 70);
    p->products[7] = Producto("Producto 8", 800, 80, 80, 8000, 800, 800, 80, 80);

    for (int i=0; i < p->amount; i++){
      p->id = i + 1;
      pthread_create(&tid, NULL, soldReport, ( void *)&p);
      
    }

    for (int i=0; i < p->amount; i++){
      pthread_join(tid, NULL); 
    }

    pthread_exit(NULL);

}


†



