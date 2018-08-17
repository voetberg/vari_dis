 #!/bin/bash

##I would loop but man. I don't know how to do the scaling

##Pt 50
##Go find scaling numbers 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_50.root\
  -o ../results/data_dis18_50.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000255616 width'\
     'n/^Background__/scale 1.00732831e-7 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_100.root\
  -o ../results/data_dis18_100.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00001276535 width'\
     'n/^Background__/scale 4.02451088e-7 width'\
  -g 'leg tr'\
  --colors=600 635



##Pt 150 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_150.root\
  -o ../results/data_dis18_150.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00009222539 width'\
     'n/^Background__/scale 0.0000021748 width'\
  -g 'leg tr'\
  --colors=600 635



##Pt 200 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_200.root\
  -o ../results/data_dis18_200.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00061881188 width'\
     'n/^Background__/scale 0.00001615326 width'\
  -g 'leg tr'\
  --colors=600 635



##Pt 250
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_250.root\
  -o ../results/data_dis18_250.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00106837606 width'\
     'n/^Background__/scale 0.00002837442 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 300
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_300.root\
  -o ../results/data_dis18_300.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00284900284 width'\
     'n/^Background__/scale 0.0000718494 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 350
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_350.root\
  -o ../results/data_dis18_350.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00675675675 width'\
     'n/^Background__/scale 0.00016455487 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_400.root\
  -o ../results/data_dis18_400.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.01408450704 width'\
     'n/^Background__/scale 0.00033288948 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400p
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_400p.root\
  -o ../results/data_dis18_400p.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00909090909 width'\
     'n/^Background__/scale 0.00027285129 width'\
  -g 'leg tr'\
  --colors=600 635

