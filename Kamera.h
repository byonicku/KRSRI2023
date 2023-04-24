class Kamera{
    private:
        Pixy2 pixy;

    public:
        Kamera(){
            
        }
        
        void init(){
            // Inisialiasai kamera
            pixy.init();
        }

        void getLocation(){
            // TODO : Get location of the object

            pixy.ccc.getBlocks();
            
            if (pixy.ccc.numBlocks){
                Serial.print("Detected ");
                Serial.println(pixy.ccc.numBlocks);

                for (int i=0; i<pixy.ccc.numBlocks; i++){
                  Serial.print("  block ");
                  Serial.print(i);
                  Serial.print(": ");
                  pixy.ccc.blocks[i].print();
                }
            }  
        }
};