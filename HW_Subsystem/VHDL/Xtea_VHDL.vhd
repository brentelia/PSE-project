
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_bit.all;

PACKAGE Xtea_VHDL_package is
    -- data size
    CONSTANT COUNTER_SIZE : INTEGER := 6;
    CONSTANT DATA_SIZE: INTEGER := 32;
    CONSTANT SUM_SIZE : INTEGER := 64;
    -- states
    CONSTANT START_ST: INTEGER := 0;
    CONSTANT IDLE_ST: INTEGER := 1; 
    CONSTANT FETCH_ST: INTEGER := 2;
    CONSTANT FETCH_ST2: INTEGER := 9; -- per implementazione
    CONSTANT FETCH_ST3: INTEGER := 10; -- per implementazione
    CONSTANT FETCH_ST4: INTEGER := 11; -- per implementazione
    CONSTANT CFR_WORD_1_ST: INTEGER := 3;
    CONSTANT DCFR_ST: INTEGER := 4;
    CONSTANT DCF_WORD_1_ST: INTEGER := 5;
    CONSTANT CFR_WORD_2_ST: INTEGER := 6;
    CONSTANT DCF_WORD_2_ST: INTEGER := 7;
    CONSTANT END_ST: INTEGER := 8;
    CONSTANT END_ST2: INTEGER := 12; -- per implementazione
    -- other constants 
    CONSTANT ZERO : UNSIGNED (SUM_SIZE-1 DOWNTO 0):="0000000000000000000000000000000000000000000000000000000000000000";
    CONSTANT UNO : UNSIGNED (SUM_SIZE-1 DOWNTO 0):="0000000000000000000000000000000000000000000000000000000000000001";
    CONSTANT DUE: UNSIGNED (SUM_SIZE-1 DOWNTO 0):= "0000000000000000000000000000000000000000000000000000000000000010";
    CONSTANT TRE: UNSIGNED (SUM_SIZE-1 DOWNTO 0):= "0000000000000000000000000000000000000000000000000000000000000011";
    CONSTANT UNDICI: UNSIGNED (DATA_SIZE-1 DOWNTO 0):= "00000000000000000000000000001011";
    CONSTANT TRENTADUE: UNSIGNED (COUNTER_SIZE-1 DOWNTO 0):="100000";
    CONSTANT DELTA_VAL: UNSIGNED (DATA_SIZE-1 DOWNTO 0):="10011110001101110111100110111001";
END Xtea_VHDL_package;

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_bit.all;
USE work.Xtea_VHDL_package.all;

ENTITY XTEA IS
    PORT(
        word0 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    --    word1 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0); --da commentare per implementazione
        key1 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0); 	
      --  key2 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0); --da commentare per implementazione
      --  key3 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0); --da commentare per implementazione
      --  key4 : in UNSIGNED (DATA_SIZE-1 DOWNTO 0); --da commentare per implementazione
        mode : in BIT;
        din_rdy : in BIT;
        reset : in BIT;
        clock : in BIT;
        word0_pr : out UNSIGNED (DATA_SIZE-1 DOWNTO 0);
      -- word1_pr : out UNSIGNED (DATA_SIZE-1 DOWNTO 0); --da commentare per implementazione
        dout_rdy1 : out BIT;
	    dout_rdy2 : out BIT 	--per implementazione
    );
END XTEA;

ARCHITECTURE XTEA_arch OF XTEA IS
    
    SIGNAL counter :UNSIGNED (COUNTER_SIZE-1 DOWNTO 0);
    SIGNAL val1 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL val2 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL k1 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL k2 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL k3 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL k4 :UNSIGNED (DATA_SIZE-1 DOWNTO 0);
    SIGNAL sum :UNSIGNED (SUM_SIZE-1 DOWNTO 0);
    SIGNAL STATUS: INTEGER RANGE 0 TO 12;
    SIGNAL NEXT_STATUS: INTEGER RANGE 0 TO 12;

BEGIN
    --FSM--
    PROCESS (STATUS, din_rdy, mode, counter)
    BEGIN
        case STATUS is
            when START_ST =>
                NEXT_STATUS <= IDLE_ST;
            when IDLE_ST =>
                if din_rdy = '1' then
                    NEXT_STATUS <= FETCH_ST;
                else
                    NEXT_STATUS <= IDLE_ST;
                end if;
            when FETCH_ST =>
		        NEXT_STATUS<=FETCH_ST2; --per implementazione
            when FETCH_ST2 =>		  --	
                  NEXT_STATUS<=FETCH_ST3; --
            when FETCH_ST3 =>             --
                  NEXT_STATUS<=FETCH_ST4; --         
            when FETCH_ST4 =>		  --per implementazione	
                if mode = '0' then
                    NEXT_STATUS<=CFR_WORD_1_ST;
                else NEXT_STATUS<=DCFR_ST;
                end if;
            when CFR_WORD_1_ST =>
                NEXT_STATUS <= CFR_WORD_2_ST;
            when CFR_WORD_2_ST =>
                if counter = TRENTADUE then
                    NEXT_STATUS <= END_ST;
                else NEXT_STATUS <=CFR_WORD_1_ST;
                end if;
            when DCFR_ST =>
                NEXT_STATUS <= DCF_WORD_1_ST;
            when DCF_WORD_1_ST =>
                NEXT_STATUS <= DCF_WORD_2_ST;
            when DCF_WORD_2_ST =>
                if counter = TRENTADUE then
                    NEXT_STATUS <= END_ST;
                else NEXT_STATUS <=DCF_WORD_1_ST;
                end if;
            when END_ST =>
                NEXT_STATUS <= END_ST2;--per implementazione
            when END_ST2 =>	       --
                NEXT_STATUS <= IDLE_ST;
            when others =>
                NEXT_STATUS <= STATUS;
        end case;
    END PROCESS;

    -- DATAPATH --
    PROCESS (clock, reset)
    BEGIN
        if reset='1' then
            STATUS <= START_ST;
        elsif clock'event and clock = '1' then
            STATUS <= NEXT_STATUS;
            case NEXT_STATUS is
                when START_ST =>
                    dout_rdy1 <= '0';
                    dout_rdy2 <= '0';
                    word0_pr <= ZERO(DATA_SIZE-1 DOWNTO 0);
                    --word1_pr <= ZERO(DATA_SIZE-1 DOWNTO 0); commentato per implemetazione
                    --delta <= DELTA_VAL;
                    val1 <= ZERO(DATA_SIZE-1 DOWNTO 0);
                    val2 <= ZERO(DATA_SIZE-1 DOWNTO 0);
                when IDLE_ST =>
                    dout_rdy1 <= '0';
                    dout_rdy2 <= '0';
                    sum <= ZERO;
                    counter <= ZERO(COUNTER_SIZE-1 DOWNTO 0);
                    val1 <= ZERO(DATA_SIZE-1 DOWNTO 0);
                    val2 <= ZERO(DATA_SIZE-1 DOWNTO 0);
                 when FETCH_ST =>	
                    val1 <= word0;
                    k1<=key1;
	        when FETCH_ST2 => --stati extra per implementazione
		            k2<=key1;
                    val2 <= word0;
                when FETCH_ST3 =>
                    k3<=key1;
                when FETCH_ST4 =>
                    k4<=key1;
                when CFR_WORD_1_ST =>
                    if (sum and TRE ) = ZERO then
                        val1 <= val1+((((val2 sll 4) xor (val2 srl 5)) +
                        val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k1));
                    elsif (sum and TRE ) = UNO then
                        val1 <= val1+((((val2 sll 4) xor (val2 srl 5)) +
                        val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k2));
                    elsif (sum and TRE ) = DUE then
                        val1 <= val1+((((val2 sll 4) xor (val2 srl 5)) +
                        val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k3));
                    else 
                        val1 <= val1+((((val2 sll 4) xor (val2 srl 5)) +
                        val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k4));
                    end if;
                    sum <= sum + DELTA_VAL;
                when CFR_WORD_2_ST =>
                    if ((sum srl 11)and TRE) = ZERO then
                        val2<=val2+((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k1));
                    elsif ((sum srl 11)and TRE) = UNO then
                        val2<=val2+((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k2));
                    elsif ((sum srl 11)and TRE) = DUE then
                        val2<=val2+((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k3));
                    else 
                        val2<=val2+((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k4));
                    end if;
                    counter <= counter + UNO(COUNTER_SIZE-1 DOWNTO 0);
                when DCFR_ST =>
                    sum <= ("00000000000000000000000000000000" & DELTA_VAL) sll 5;
                when DCF_WORD_1_ST =>
                    if((sum srl 11) and TRE) = ZERO then
                        val2<=val2-((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k1));
                    elsif((sum srl 11) and TRE) = UNO then
                        val2<=val2-((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k2));
                    elsif((sum srl 11) and TRE) = DUE then
                        val2<=val2-((((val1 sll 4) xor (val1 srl 5)) +
                            val1) xor (sum(DATA_SIZE-1 DOWNTO 0) +  k3));
                    else
                        val2<=val2-((((val1 sll 4) xor (val1 srl 5)) +
                          val1) xor (sum(DATA_SIZE-1 DOWNTO 0) + k4));
                    end if;
                    sum <= sum-DELTA_VAL;
                when DCF_WORD_2_ST =>
                    if (sum and TRE) = ZERO then
                        val1<=val1-((((val2 sll 4) xor (val2 srl 5)) +
                            val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k1));
                    elsif (sum and TRE) = UNO then
                        val1<=val1-((((val2 sll 4) xor (val2 srl 5)) +
                            val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k2));
                    elsif (sum and TRE) = DUE then
                        val1<=val1-((((val2 sll 4) xor (val2 srl 5)) +
                            val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k3));
                    else 
                        val1<=val1-((((val2 sll 4) xor (val2 srl 5)) +
                        val2) xor (sum(DATA_SIZE-1 DOWNTO 0) + k4));
                    end if;
                    counter<= counter + UNO(COUNTER_SIZE-1 DOWNTO 0);
                when END_ST =>
                    word0_pr <= val1;
                    dout_rdy1 <='1';
                when END_ST2 =>--stato extra per implementazione
                    word0_pr <= val2;
                    dout_rdy1 <='0';
                    dout_rdy2 <='1';
                when others =>
                    dout_rdy1 <= '0';
                    dout_rdy2 <= '1';
                    word0_pr <= ZERO(DATA_SIZE-1 DOWNTO 0);
            end case;
        end if;
    END PROCESS;
END XTEA_arch;
                    



