 #!/bin/bash

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_mcbg.pdf \
  -e 's/^(Signal__mc|Bckground__mc)__//' \
     'nl/^(Signal|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_mcleft.pdf \
  -e 's/^(Signal__mc|Left__mc)__//' \
     'nl/^(Signal|Left).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_dataright.pdf \
  -e 's/^(Signal__data|Right__data)__//' \
     'nl/^(Signal|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_databg.pdf \
  -e 's/^(Signal__data|Bckground__data)__//' \
     'nl/^(Signal|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_dataleft.pdf \
  -e 's/^(Signal__data|Left__data)__//' \
     'nl/^(Signal|Left).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38

hed /msu/data/t3work9/voetberg/vari_dist/pt_ratio_dis.root\
  -o ../results/ptratio_dataright.pdf \
  -e 's/^(Signal__data|Right__data)__//' \
     'nl/^(Signal|Right).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Right__/norm'\
  -g 'leg tr'\
  --colors=40 41 42 43 46 47 30 33 38
