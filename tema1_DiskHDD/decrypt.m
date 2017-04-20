function [] = decrypt() 

	file_matrice = fopen("key1B", "r");
	file_string = fopen("input1B", "r");
	file_write = fopen("output1B", "w");

	n = fscanf(file_matrice, "%d", 1);
	A = zeros(n);

	A = fscanf(file_matrice, "%d", [n n]);
	str = fscanf(file_string, "%c", inf);

	%A = A'; % octave citeste aiurea matricile din cauza lui fscanf
	D = columns(str);
	

	for i = 1:D
		V(i) = convert_int(str(i));
	end

	new_d = D;

	while(mod(new_d, n) != 0) % umplu cu zerouri pentru a forma blocuri de n elemente
		new_d = new_d  + 1;
		V(new_d) = 0;
	end

	C = inversa_gauss(A);
	
	for i = 1:new_d/n %new_d / n inmultiri cu matricea

		B = V( (i - 1) * n + 1: i * n) * C; % selectez cele n elemente care ma intereseaza si inmultesc cu matricea A
		B = mod(B, 29);
		
		for j = 1:n
			contor = fprintf(file_write, "%c", convert_char(B(j)));
		end	

	end