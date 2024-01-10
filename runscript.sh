g++ test_gen.cpp -lgmp -lgmpxx
g++ test_box.cpp -lgmp -lgmpxx
./eitre eloop.ptre testBlowup.csv 3 pos_labels.txt neg_labels.txt
./mptre intersection.ptre testInter.csv 3
./mptre porv.ptre real_signal.csv 3
./mptre neg_porv.ptre real_signal.csv 3
./mptre porv.ptre real_signal.csv 3 porv_pos.txt porv_neg.txt
./mptre neg_porv.ptre real_signal.csv 3 porv_pos.txt porv_neg.txt
./mptre paramecg.ptre debugTest.csv 3 pos_ecg.txt neg_ecg.txt
# EITRE Scalability test
./eitre escaletest1.ptre testBlowup.csv 1
./eitre escaletest3.ptre testBlowup.csv 3
./eitre escaletest5.ptre testBlowup.csv 5
./eitre escaletest7.ptre testBlowup.csv 7