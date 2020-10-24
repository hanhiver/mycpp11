build :
	g++ -o get_cpu_id get_cpu_id.cpp
	g++ -o get_mac_address get_mac_address.cpp
	g++ -o get_hd_id get_hd_id.cpp
	g++ -o get_mb_id get_mb_id.cpp

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
	-rm get_cpu_id
	-rm get_mac_address
	-rm get_hd_id
	-rm get_mb_id

rebuild : clean build