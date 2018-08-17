 #!/bin/bash

##Pt 50
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_50.root\
  -o ../results/mc_dis_50.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000149243 width'\
     'n/^Background__/scale 0.00000187188 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_100.root\
  -o ../results/mc_dis_100.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000127714 width'\
     'n/^Background__/scale 0.00000191122 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 150 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_150.root\
  -o ../results/mc_dis_150.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000290613 width'\
     'n/^Background__/scale 0.00000824313 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 200 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_200.root\
  -o ../results/mc_dis_200.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00000519726 width'\
     'n/^Background__/scale 0.00003243593 width'\
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
     'n/^Background__/scale 0.00017882689 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 350 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_350.root\
  -o ../results/mc_dis_350.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00002122511 width'\
     'n/^Background__/scale 0.00036630036 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_400.root\
  -o ../results/mc_dis_400.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.0000314495 width'\
     'n/^Background__/scale 0.00072254335 width'\
  -g 'leg tr'\
  --colors=600 635

##Pt 400p 
hed /msu/data/t3work9/voetberg/vari_dist/mc_dis_400p.root\
  -o ../results/mc_dis_400p.pdf \
  -e 's/^(Signal|Background)__//' \
     'nl/^(Signal|Background).*/\1/' \
     'n/^Signal__/scale 0.00001130186 width'\
     'n/^Background__/scale 0.00036101083 width'\
  -g 'leg tr'\
  --colors=600 635

