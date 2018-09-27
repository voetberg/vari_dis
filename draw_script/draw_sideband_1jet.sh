 #!/bin/bash

##Pt 50
hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt50_1jet.root\
  -o ../results/data_sideband_1jet_50.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 100 
hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt100_1jet.root\
  -o ../results/data_sideband_1jet_100.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

##Pt 150 

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt150_1jet.root\
  -o ../results/data_sideband_1jet_150.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46

##Pt 200 


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt200_1jet.root\
  -o ../results/data_sideband_1jet_200.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 250

hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt250_1jet.root\
  -o ../results/data_sideband_1jet_250.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 300


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt300_1jet.root\
  -o ../results/data_sideband_1jet_300.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 350


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt350_1jet.root\
  -o ../results/data_sideband_1jet_350.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 400


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400_1jet.root\
  -o ../results/data_sideband_1jet_400.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


##Pt 400p


hed /msu/data/t3work9/voetberg/vari_dist/Variable_Dist_pt400p_1jet.root\
  -o ../results/data_sideband_1jet_400p.pdf \
  -e 's/^(Signal__data|Left__data|Right__data|Bckground__data)__//' \
     'nl/^(Signal|Left|Right|Bckground).*/\1/' \
     'n/^Signal__/norm'\
     'n/^Left__/norm'\
     'n/^Right__/norm'\
     'n/^Bckground__/norm'\
  -g 'leg tr'\
  --colors=9 8 41 46


