#include <iostream>
#include <string>
using namespace std  ;



template <typename data_type>
class HashTable{
private:
    struct NodeBucket{ 
        data_type valor ; 
        int clave ; 
        NodeBucket* next;

        NodeBucket(int key,data_type val){
            valor = val ; 
            clave = key ; 
            next = nullptr ; 
        }
    };

    NodeBucket** Lista_Buckets; 
    int N_Buckets ; 
    int N_pares_total ; 
    float Umbral ; 


    int Hash(int key){
        return key % N_Buckets ; 
    }
    
    void Rehashing(){
        NodeBucket** lista_vieja = Lista_Buckets ; 
        int n_buckets_antiguo = N_Buckets ; 
        
        N_Buckets = n_buckets_antiguo * 2 ;  // nuevo tamañito
        Lista_Buckets = new NodeBucket*[N_Buckets] ;  // nueva lista de buckets 

        for (int i = 0 ; i <N_Buckets ; i++ ){ // inicializamos la lista
            Lista_Buckets[i] = nullptr ; 
        }        

        // ahora si empezamos a insertas los antiguos nodos a esta nueva lista
        for (int i = 0 ;  i < n_buckets_antiguo ; i++){
            NodeBucket* Nodo_BucketBorrar = lista_vieja[i] ; 
            if (Nodo_BucketBorrar == nullptr){ // osea si estbaa vacio este bucket no hay que pasar nada 
                continue ; 
            }

            while(Nodo_BucketBorrar != nullptr){
                // guardamos el next de el nodo a borrar para avanzar al siguiente antes de perderlo al borrar Nodo_BucketBorrar
                NodeBucket* siguiente = Nodo_BucketBorrar->next ; 
                Nodo_BucketBorrar->next = nullptr ;  // desligamos este nodo 
                int bucket = Hash(Nodo_BucketBorrar->clave) ; 
                NodeBucket* nuevo = Nodo_BucketBorrar ;  // creamos uno nuevo con los valores de nodobucket borrar
                
                if (Lista_Buckets[bucket]==nullptr){ // si es que es el primero en entrar
                    Lista_Buckets[bucket] =nuevo ;  
                }else{ // si es que si esta lleno 
                    NodeBucket* guardado = Lista_Buckets[bucket] ; 
                    Lista_Buckets[bucket] = nuevo ; 
                    nuevo->next = guardado ; 
                }

                Nodo_BucketBorrar = siguiente ; 


            }
                  
        }
        delete[] lista_vieja ; 


    }
    
public:
    HashTable(int N){
        N_Buckets = N ; 
        N_pares_total = 0 ; 
        Umbral = 0.75 ; 
        Lista_Buckets = new NodeBucket*[N_Buckets] ; 
        
        for (int i = 0 ; i < N_Buckets ; i++){
            Lista_Buckets[i] = nullptr ; 
        }

        
    }
    
    void Insertar(int key , data_type val){
        
        int Bucket = Hash(key) ; 
        NodeBucket* temp = Lista_Buckets[Bucket] ; 
        
        if (temp == nullptr){
            NodeBucket* nuevo = new NodeBucket(key,val) ; 
            Lista_Buckets[Bucket] = nuevo ; 
            N_pares_total++ ; 

            if ((float)N_pares_total / N_Buckets > Umbral) {
                Rehashing();
            }
            return ; 
        }

        while(temp != nullptr){
            if (temp->clave == key){
                temp->valor = val ; 
                break ; 
            }

            if (temp->next == nullptr && temp->clave != key){ // significa que no lo encontro
                NodeBucket* nuevo = new NodeBucket(key,val) ; 
                NodeBucket* temp2 = Lista_Buckets[Bucket] ; 
                nuevo->next = temp2 ; 
                Lista_Buckets[Bucket] = nuevo ; 
                N_pares_total++ ; 
                break ; 
            }
            temp=temp->next ; 
        }

        // pendiente hacer evaluar el rehashing en base al umbral 

        if ((float)N_pares_total / N_Buckets > Umbral) {
            Rehashing();
        }

    }


    data_type buscar(int key){
        int bucket = Hash(key);
        NodeBucket* temp = Lista_Buckets[bucket];

        if (temp == nullptr){
            cout << "No existe esta llave " << key << " en la tabla\n" ; 
            return data_type{};
        }

        while(temp != nullptr){
            if (temp->next == nullptr && temp->clave != key){ // no lo encontro
                cout << "No existe esta llave " << key << " en la tabla\n" ; 
                return data_type{};
            }
            if (temp->clave == key){
                return temp->valor ; 
            }
            temp = temp->next ; 
        }
        
        cout << "No existe esta llave " << key << " en la tabla\n" ; 
        return data_type{};
    }

    void Eliminar(int key){
        int bucket = Hash(key);
        NodeBucket* temp = Lista_Buckets[bucket] ; 

        if(temp == nullptr){
            cout << "No existe esta llave " << key << " en la tabla\n" ; 
            return ; 
        }

        if (temp->clave  == key ){ // la cabeza es la que quieres eliminar 
            Lista_Buckets[bucket] = temp->next ;
            delete temp ; 
            N_pares_total--;
            return ;  
        }else{ // sino los siquientes  
            while(temp->next != nullptr){
                if ((temp->next)->clave == key){
                    cout << "La llave " << key << " se elimino con el valor de " << (temp->next)->valor << endl ; 
                    NodeBucket* borrar = temp->next ; 
                    NodeBucket* guardar = borrar->next;
                    temp->next = guardar ;
                    delete borrar ;  
                    N_pares_total-- ; 
                    
                    return ; 
                }
                temp = temp->next ; 
            }
            cout << "No existe esta llave " << key << " en la tabla\n" ; 
        }

        

    }


};




int main(){
    // pruebasssssss

    

    cout << endl ; 
    return 0 ; 
}



