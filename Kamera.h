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

        int getKorban(){
            pixy.ccc.getBlocks();

            if (pixy.ccc.numBlocks){
                for (int i = 0; i < pixy.ccc.numBlocks; i++){
                    return i;
                }
            }

            return -1;
        }

        int getWidth(){
            int i = getKorban();
            
            if(i == -1) return -1;

            return pixy.ccc.blocks[i].m_width;
        }

        int getHeight(){
            int i = getKorban();
              
            if(i == -1) return -1;
            
            return pixy.ccc.blocks[i].m_height;
        }
        
        int getX(){
            int i = getKorban();
              
            if(i == -1) return -1;

            return pixy.ccc.blocks[i].m_x;
        }

        int getY(){
            int i = getKorban();
            
            if(i == -1) return -1;

            return pixy.ccc.blocks[i].m_y;
        }

        void printLocationDummy(){
            // TODO : Get location of the object
            
            // KANAN X SEMAKIN BESAR
            // KIRI X SEMAKIN KECIL

            // WIDTH SEMAKIN JAUH SEMAKIN KECIL -> BISA UNTUK MENENTUKAN BERAPA LANGKAH KE KORBAN

            // HEIGHT SEMAKIN DEKAT SEMAKIN BESAR 

            //pixy.ccc.blocks[i].m_width -> variabel width
            //pixy.ccc.blocks[i].m_height -> variabel height

            pixy.ccc.getBlocks();
            
            if (pixy.ccc.numBlocks){
                for (int i=0; i<pixy.ccc.numBlocks; i++){
                  Serial.print("Width : ");
                  Serial.println(pixy.ccc.blocks[i].m_width);
                  Serial.print("Height : ");
                  Serial.println(pixy.ccc.blocks[i].m_height);
                  Serial.print("X : ");
                  Serial.println(pixy.ccc.blocks[i].m_x);
                  Serial.print("Y : ");
                  Serial.println(pixy.ccc.blocks[i].m_y);
                  delay(500);
                }
            }  
        }
};