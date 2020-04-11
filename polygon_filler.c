void draw_triangles(UBYTE *chunky, WORD *points, WORD chunky_width) {
    WORD i, idx = 0;
    UBYTE *ptr;
    for (i = 0; i <= points[0]; i++) {
        WORD x1 = points[i*8+1],
             y1 = points[i*8+2],
             x2 = points[i*8+3],
             y2 = points[i*8+4],
             x3 = points[i*8+5],
             y3 = points[i*8+6],
             color = points[i*8+7],
             tmpx, tmpy, y, x, scx1, scx2, swap = 0;
        LONG dx1 = 0, dx2 = 0, dx3 = 0, dxt = 0, scanleft, scanright, leftadd, rightadd;

        if (y2 > y3)
        {
            tmpx = x2;
            tmpy = y2;
            x2 = x3;
            y2 = y3;
            x3 = tmpx;
            y3 = tmpy;
        }
        
        if (y1 > y2)
        {
            tmpx = x1;
            tmpy = y1;
            x1 = x2;
            y1 = y2;
            x2 = tmpx;
            y2 = tmpy;
        }
        
        if (y2 > y3)
        {
            tmpx = x2;
            tmpy = y2;
            x2 = x3;
            y2 = y3;
            x3 = tmpx;
            y3 = tmpy;
        }
        if (y2 != y1)
            dx1 = ((x2 - x1) << 6) / (y2 - y1);
        if (y3 != y1)
            dx2 = ((x3 - x1) << 6) / (y3 - y1);
        if (y3 != y2)
            dx3 = ((x3 - x2) << 6) / (y3 - y2);
        
        scanleft = x1 << 6;
        scanright = x1 << 6;
     
        ptr = &chunky[y1*WIDTH];
    
        if (dx2 < dx1) {
            dxt = dx2;
            dx2 = dx1;
            dx1 = dxt;
            swap = 1;
        }
        
        for (y = y1; y < y2; y++) {
            scx1 = scanleft>>6;
            scx2 = (scanright>>6)+((scanright&0x3f)>0x1f?1:0);
            for (x = scx1; x < scx2; x++) {
                ptr[x] = color;    
            }       
            scanleft+=dx1;
            scanright+=dx2; 
            ptr+=chunky_width;
        }
        
        if (swap!=0) {
            dxt = dx2;
            dx2 = dx1;
            dx1 = dxt;
        }
        if (dx2 < dx3) {
            dx1=dx3;
            if (y1 == y2) {
                scanleft = x2 << 6;
                scanright = x1 << 6;
            }
        }
        else
        {
            dx1 = dx2;
            dx2 = dx3;
            if (y1 == y2) {
                scanleft = x1 << 6;
                scanright = x2 << 6;
            }
        }

        for (y = y2; y <= y3; y++) {
            scx1 = scanleft>>6;
            scx2 = (scanright>>6)+((scanright&0x3f)>0x1f?1:0);
            for (x = scx1; x < scx2; x++) {
                ptr[x] = color;    
            }       
            scanleft+=dx1;
            scanright+=dx2; 
            ptr+=chunky_width;
        }
    }
}
