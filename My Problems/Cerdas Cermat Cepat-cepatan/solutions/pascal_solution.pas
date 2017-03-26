program cari_cara;

const
	MODULO = 1000000007;

var
	n : longint;
	factors, revFactors, dp: array[1..2000] of int64;
	factorSize: longint;
	revFactorSize: longint;

procedure generateFactors(x : longint);
var
	i : longint;
begin
	i := 2;
	while i*i <= x do
		begin
			if x mod i = 0 then
				begin
					factors[factorSize] := i;
					inc(factorSize);

					if i*i <> x then
						begin
							revFactors[revFactorSize] := x div i;
							inc(revFactorSize);
						end;
				end;
			inc(i);
		end;

	for i := revFactorSize-1 downto 0 do
		begin
			factors[factorSize] := revFactors[i];
			inc(factorSize);
		end;

	factors[factorSize] := x;
	inc(factorSize);
end;

function getIndex(x : longint): longint;
var
	low, mid, hi : longint;
begin
	low := 0;
	hi := factorSize-1;

	while low < hi do
		begin
			mid := (low + hi) div 2;
			if factors[mid] >= x then
				hi := mid
			else
				low := mid+1;
		end;

	exit(low);
end;

procedure bottomUp();
var
	i, j, x, idx : longint;
	isPrime : boolean;
begin
	for i := 0 to factorSize-1 do
		begin
			isPrime := true;
			for j := 0 to i do
				if ((factors[i] mod factors[j]) = 0) and (factors[j] <= (factors[i] div factors[j])) then
					begin
						isPrime := false;
						x := factors[j];

						idx := getIndex(factors[i] div x);

						if j <> idx then
							begin
								dp[i] := (dp[i] + dp[j] * dp[idx]) mod MODULO;
							end
						else
							begin
								dp[i] := (dp[i] + (dp[j]+1) * dp[j] div 2) mod MODULO;
							end;
					end;

			if isPrime then
				dp[i] := 1;

		end;
end;

begin
	readln(n);
	generateFactors(n);
	bottomUp();
	writeln(dp[factorSize-1]);
end.