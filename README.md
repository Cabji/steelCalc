# Steel Calculator

This project aims to be a useful tool for calculating info about steel reinforcment in concrete slabs.

# Current Aim

- Fix sizer bug when UpdateResults() is called: sizer/widgets are not automatically adjusting size to fit required information in them
- Continue code for auto-calculations when user changes input values. Use  SteelCalcMain::UpdateResults().
  - Calculate bar Area value
  - Determine bar processing type (count how many length values there are)
  - Calculate Cost per Mg
  - Calculate total Weight

# To Do

  - Handle switch of UI widgets to allow entering size specs for circular shaped steel

# Planned Features (Subject to Change)

1. Bar quantity calculator
2. Total tonnage (Mg) calculations
3. Steel Fixing Units (SFUs) calculator
4. ... (more to come as I think of them)