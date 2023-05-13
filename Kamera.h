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

         void kameraPrintLocation(){
            Serial.print(getX());
            Serial.print(", ");
            Serial.print(getY());
            Serial.print(", ");
            Serial.print(getWidth());
            Serial.print(", ");
            Serial.println(getHeight());
        }
};