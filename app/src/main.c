#include <xs1.h>
#include <platform.h>

extern int tile[2];

void enable_secondary_output_divider_by_4(void) {
    // output divide by 4 start
    #define APP_CLK_VAL 0x80000003
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_CLK_DIVIDER_NUM, APP_CLK_VAL);
    // output divide by 4 end
}

void mipi_app_clock_divide_by_2(void) {
    // MIPI clock divider by 2 start
    #define MIPI_CLK_VAL 0x80000000
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_MIPI_CLK_DIVIDER_NUM, MIPI_CLK_VAL);
    // MIPI clock divider by 2 end
}

void lpddr_app_clock_divide_by_2(void) {
    // LPDDR clock divider by 4 start
    #define DDR_CLK_VAL 0x80000001
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_DDR_CLK_DIVIDER_NUM, DDR_CLK_VAL);
    // LPDDR clock divider by 4 end
}

void frac_divider_20_38_4(void) {
    // FRAC divider 20 38.4 start
    #define PLL_VAL_1 0x02004B03
    #define PLL_FRACT_VAL_1 0x80000405
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, 0); // Enable
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, PLL_VAL_1);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_FRAC_N_DIVIDER_NUM, PLL_FRACT_VAL_1);
    // FRAC divider 20 38.4 end
}

void frac_divider_11_25(void) {
    // FRAC divider 11 25 start
    #define PLL_VAL_2 0x02003C04
    #define PLL_FRACT_VAL_2 0x80000B19
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, 0); // Enable
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, PLL_VAL_2);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_FRAC_N_DIVIDER_NUM, PLL_FRACT_VAL_2);
    // FRAC divider 11 25 end
}


void frac_divider_29_28(void) {
    // APP PLL 29.28 start
    #define PLL_VAL 0x02003C04
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, 0); // Enable
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_SS_APP_PLL_CTL_NUM, PLL_VAL);
    // APP PLL 29.28 end
}


// PLL bypass start
unsigned pllCtrlVal;

void pll_bypass_on(void) {
    #define PLL_VAL_BYPASS   0xE0000000
    setps(XS1_PS_XCORE_CTRL0,0x10);
    read_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM, &pllCtrlVal);
    write_pswitch_reg(get_local_tile_id(), XS1_PSWITCH_PLL_CLK_DIVIDER_NUM, 5);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM,
                          pllCtrlVal          | PLL_VAL_BYPASS);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM,
                          (pllCtrlVal& ~0xFFF)| PLL_VAL_BYPASS);
}

void pll_bypass_off(void) {
    write_pswitch_reg(get_local_tile_id(), XS1_PSWITCH_PLL_CLK_DIVIDER_NUM, 0);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM,
                          pllCtrlVal | PLL_VAL_BYPASS);
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM,
                          pllCtrlVal | 0xC0000000    );
}
// PLL bypass end

void tile_clock_250_MHz() {
// Tile clock half speed start
    write_pswitch_reg(get_local_tile_id(), XS1_PSWITCH_PLL_CLK_DIVIDER_NUM, 1);
    setps(XS1_PS_XCORE_CTRL0,0x10);
// Tile clock half speed end
}

void switch_clock_low_speed() {
// Switch clock low speed start
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_CLK_DIVIDER_NUM, 499);
// Switch clock low speed end
}

void ref_clock_max_speed() {
// Ref clock max speed start
    write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_REF_CLK_DIVIDER_NUM, 0x01);
// Ref clock max speed end
}

void flip_system_clock_once_12() {
// Flip system clock to new value 12 on reset start
    // This code should be called early on in main once
    #define PLL_VAL_12MHz 0x0100F700
    unsigned oldValue;
    read_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM, &oldValue);
    if (oldValue != PLL_VAL_12MHz) {
        write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM, PLL_VAL_12MHz);
    }
// Flip system clock to new value 12 on reset end
}

void flip_system_clock_once_24() {
// Flip system clock to new value 24 on reset start
    // This code should be called early on in main once
    #define PLL_VAL_24MHz 0x01007C00
    unsigned oldValue;
    read_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM, &oldValue);
    if (oldValue != PLL_VAL_24MHz) {
        write_sswitch_reg(get_local_tile_id(), XS1_SSWITCH_PLL_CTL_NUM, PLL_VAL_24MHz);
    }
// Flip system clock to new value 24 on reset end
}

int main(void) {
//    flip_system_clock_once_12();
    flip_system_clock_once_24();
    enable_secondary_output_divider_by_4();
    mipi_app_clock_divide_by_2();
    lpddr_app_clock_divide_by_2();
    frac_divider_20_38_4();
    frac_divider_11_25();
    frac_divider_29_28();
    pll_bypass_on();
    pll_bypass_off();
    tile_clock_250_MHz();
    switch_clock_low_speed();
    ref_clock_max_speed();
}
