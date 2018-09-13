 #!/bin/bash

##I would loop but man. I don't know how to do the scaling

##Pt 50
##Go find scaling numbers 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_50.root\
  -o ../results/data_dis18_50.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_100.root\
  -o ../results/data_dis18_100.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65
 


##Pt 150 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_150.root\
  -o ../results/data_dis18_150.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65 



##Pt 200 
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_200.root\
  -o ../results/data_dis18_200.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65



##Pt 250
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_250.root\
  -o ../results/data_dis18_250.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

##Pt 300
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_300.root\
  -o ../results/data_dis18_300.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

##Pt 350
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_350.root\
  -o ../results/data_dis18_350.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

##Pt 400
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_400.root\
  -o ../results/data_dis18_400.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

##Pt 400p
hed /msu/data/t3work9/voetberg/vari_dist/real_dis_400p.root\
  -o ../results/data_dis18_400p.pdf \
  -e 's/^(Signal|Left|Right)__//' \
     'nl/^(Signal|Left|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=600 635 65

