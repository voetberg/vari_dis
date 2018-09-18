 #!/bin/bash

##Pt 50
hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt50.root\
  -o ../results/data_sideband_50.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt50.root\
  -o ../results/mc_sideband_50.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt100.root\
  -o ../results/data_sideband_100.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt100.root\
  -o ../results/mc_sideband_100.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 150 

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt150.root\
  -o ../results/data_sideband_150.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt150.root\
  -o ../results/mc_sideband_150.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 200 


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt200.root\
  -o ../results/data_sideband_200.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt200.root\
  -o ../results/mc_sideband_200.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

##Pt 250

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt250.root\
  -o ../results/data_sideband_250.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt250.root\
  -o ../results/mc_sideband_250.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 300


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt300.root\
  -o ../results/data_sideband_300.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt300.root\
  -o ../results/mc_sideband_300.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 350


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt350.root\
  -o ../results/data_sideband_350.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt350.root\
  -o ../results/mc_sideband_350.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 400


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400.root\
  -o ../results/data_sideband_400.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400.root\
  -o ../results/mc_sideband_400.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

##Pt 400p


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400p.root\
  -o ../results/data_sideband_400p.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400p.root\
  -o ../results/mc_sideband_400p.pdf \
  -e 's/^(Signal__mc|Left__mc|Right__mc|Bckground__mc)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

