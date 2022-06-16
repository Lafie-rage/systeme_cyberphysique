/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem_data.c
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Jun 15 14:40:11 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Subsystem.h"
#include "Subsystem_private.h"

/* Block parameters (default storage) */
P_Subsystem_T Subsystem_P = {
  /* Variable: A_bar
   * Referenced by: '<S2>/Gain10'
   */
  { -50.0, 1.0, 0.0, 0.0, 0.0, 0.0, 2500.0, 0.0, 0.0 },

  /* Variable: B_bar
   * Referenced by: '<S2>/Gain9'
   */
  { 2500.0, 0.0, 0.0 },

  /* Variable: C_bar
   * Referenced by: '<S2>/Gain11'
   */
  { 0.0, 1.0, 0.0 },

  /* Variable: Ki
   * Referenced by: '<S1>/Gain2'
   */
  -1.4999999999999933,

  /* Variable: Kx
   * Referenced by: '<S1>/Gain1'
   */
  0.029999999999999565,

  /* Variable: L_bar
   * Referenced by: '<S2>/Gain12'
   */
  { 16875.0000000001, 250.00000000000082, 375.00000000000222 },

  /* Expression: 0
   * Referenced by: '<S2>/x_est'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Integrator1'
   */
  0.0,

  /* Expression: 9
   * Referenced by: '<S1>/Saturation1'
   */
  9.0,

  /* Expression: -9
   * Referenced by: '<S1>/Saturation1'
   */
  -9.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
