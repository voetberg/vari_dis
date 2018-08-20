 #!/bin/bash

##Pt 50
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_50.root\
  -o ../results/mc_dis_50.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000149146 width'\
     'n/^Background__/scale 0.00000249992 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_100.root\
  -o ../results/mc_dis_100.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000127766 width'\
     'n/^Background__/scale 0.00000254848 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 150 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_150.root\
  -o ../results/mc_dis_150.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000290034 width'\
     'n/^Background__/scale 0.00001099807 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 200 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_200.root\
  -o ../results/mc_dis_200.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000517668 width'\
     'n/^Background__/scale 0.00004328067 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 250 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_250.root\
  -o ../results/mc_dis_250.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000871748 width'\
     'n/^Background__/scale 0.00008689607 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 300 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_300.root\
  -o ../results/mc_dis_300.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00001390395 width'\
     'n/^Background__/scale 0.00024201355 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 350 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_350.root\
  -o ../results/mc_dis_350.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.0000211479 width'\
     'n/^Background__/scale 0.00048638132 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_400.root\
  -o ../results/mc_dis_400.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.0000315527 width'\
     'n/^Background__/scale 0.00096525096 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400p 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_400p.root\
  -o ../results/mc_dis_400p.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00001129458 width'\
     'n/^Background__/scale 0.00048332527 width'\
  -g 'leg tr'\
  --colors=600 635

