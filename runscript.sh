g++ test_gen.cpp -lgmp -lgmpxx
g++ test_box.cpp -lgmp -lgmpxx
./eitre eloop.ptre testBlowup.csv 3 pos_labels.txt neg_labels.txt
./mptre intersection.ptre testInter.csv 3
./mptre porv.ptre real_signal.csv 3
./mptre neg_porv.ptre real_signal.csv 3
./mptre porv.ptre real_signal.csv 3 porv_pos.txt porv_neg.txt
./mptre neg_porv.ptre real_signal.csv 3 porv_pos.txt porv_neg.txt
./mptre edge_porv.ptre test_edge_porv.csv 2
./mptre temperature_switch.ptre temperature_data.csv 2
./mptre ecgpeak.ptre debugTest.csv 1
./mptre ecgedge.ptre debugTest 3
./mptre ecglocal.ptre debugTest.csv 3
./mptre paramecg.ptre debugTest.csv 3 pos_ecg.txt neg_ecg.txt
# MPTRE Scalability test 1
./mptre mpscaletest2.ptre debugTest.csv 2 pos_ecg.txt neg_ecg.txt >logmpscale2
./mptre mpscaletest3.ptre debugTest.csv 3 pos_ecg.txt neg_ecg.txt >logmpscale3
./mptre mpscaletest4.ptre debugTest.csv 4 pos_ecg.txt neg_ecg.txt >logmpscale4
./mptre mpscaletest5.ptre debugTest.csv 5 pos_ecg.txt neg_ecg.txt >logmpscale5
./mptre mpscaletest6.ptre debugTest.csv 6 pos_ecg.txt neg_ecg.txt >logmpscale6
# MPTRE Scalability test 2
./mptre mparamscale1.ptre debugTest.csv 2 pos_ecg.txt neg_ecg.txt >logmparam1
./mptre mparamscale2.ptre debugTest.csv 3 pos_ecg.txt neg_ecg.txt >logmparam2
./mptre mparamscale3.ptre debugTest.csv 4 pos_ecg.txt neg_ecg.txt >logmparam3
./mptre mparamscale4.ptre debugTest.csv 5 pos_ecg.txt neg_ecg.txt >logmparam4
./mptre mparamscale5.ptre debugTest.csv 6 pos_ecg.txt neg_ecg.txt >logmparam5
# EITRE Scalability test
./eitre escaletest1.ptre testBlowup.csv 1 >logest1
./eitre escaletest3.ptre testBlowup.csv 3 >logest3
./eitre escaletest5.ptre testBlowup.csv 5 >logest5
./eitre escaletest7.ptre testBlowup.csv 7 >logest7