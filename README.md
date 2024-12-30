# Steel Calculator

This project aims to be a useful tool for calculating info about steel reinforcment in concrete slabs.

# Current Aims

- Add Circular shape input checkbox toggle handler
  - Switch circular input wxGrid for lineal input wxGrid widgets in the layout

- Continue code for auto-calculations when user changes input values. Use  SteelCalcMain::UpdateResults().
  - Determine bar processing type (count how many length values there are)
  - Calculate Cost per Mg
  - Calculate total Weight

- When grid cell enters edit mode, select all text in the cell

# Planned Features (Subject to Change)

1. Bar quantity calculator
2. Total tonnage (Mg) calculations
3. Steel Fixing Units (SFUs) calculator
4. Specs for an item should be able to be packaged up and saved in the larger project (Grun) planned for the future.
