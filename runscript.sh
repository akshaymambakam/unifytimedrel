g++ test_gen.cpp -lgmp -lgmpxx
g++ test_box.cpp -lgmp -lgmpxx
./eitre eloop.ptre testBlowup.csv 3 pos_labels.txt neg_labels.txt