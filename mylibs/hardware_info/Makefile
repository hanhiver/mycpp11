build :
	g++ -o get_cpu_id.out get_cpu_id.cpp
	g++ -o get_mac_address.out get_mac_address.cpp
	g++ -o get_hd_id.out get_hd_id.cpp
	g++ -o get_mb_id.out get_mb_id.cpp
	g++ -o cpu_id_loop.out cpu_id_loop.cpp

run   :
	@echo "--------------------"
	@- ./get_cpu_id
	@echo "--------------------"
	@- ./get_mac_address
	@echo "--------------------"
	@- ./get_hd_id
	@echo "--------------------"
	@- ./get_mb_id
	@echo "--------------------"

clean : 
	-rm get_cpu_id.out
	-rm get_mac_address.out
	-rm get_hd_id.out
	-rm get_mb_id.out
	-rm cpu_id_loop.out

rebuild : clean build