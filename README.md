# Steel Calculator

This project aims to be a useful tool for calculating info about steel reinforcment in concrete slabs.

This has been developed as a simple calculator tool at first, but as time goes on I may continue developing it a bit more as it is pretty useful as a standalone tool.

## What can it do? 

Currently the calculator is simple. 

It lets you define an 'Item' which should be understood as *unique specification of a shaped bar* with its own properties such as: 
 * steel grade and diameter
 * Ln values (the length of each 'side' of the Item which results in the shape and size of the Item)
 * tag name
 * general type (Dummy Bar, Stock Bar, Starter Bar, Lig, HiHat etc. for examples) 
 
 Right now the calculator only supports an Item having a grade/bar thickness and its Ln values. It supports designing a circular shaped Item as well.

Once an Item is specified the calculator will automatically calculate pertinent Total values ('Totals') about the Item like total tonnage and estimated cost for the total amount of Items.

## Calculating Labour

The calculator can roughly calculate how many 'ties' will be needed to fix out an area of bars laid as a grid. To do this it needs to know: 

1. The area dimensions (Length and Width)
2. The center spacing of the A and B layer bars in both directions
3. The center spacing of the tie fixout pattern (usually 800mm)

You can also configure under File -> Options to include Perimeter, Setups and Lap ties for the area, and the calculator [currently] makes some assumptions  and will calculate roughly how many ties that will be.

To convert ties into labour time (man hours/minutes) you need to calculate the result it gives by how much time it takes to complete a single tie. The calculator does not calculate anything associated with lugging or laying the bars when steel fixing.

# Future Ideas

Recently I did an update on this tool, and I think I would like to add a few more configuration options, and then potentially as time goes on, also add the ability to build an array of Items in the program, aka a 'Steel Schedule'.

There is no estimated completion date for the project.

# Current Development Aims

- Configuration options
  - Redo using wxGrid for Cost per Mg for each grade/diameter of steel bar
    - Sanitization/formatting of input data (no c&b emoji strings thx!)
  - Steel mass
  - Unit of measure to use
  - Unit of currency to use
- Array of Items (Steel Scheduling)
  - Create a data structure to build a group of Items
- When grid cell enters edit mode, select all text in the cell

# Planned Features (Subject to Change)

1. Create an array of Items (bars/ligs etc.) inside the program which all contribute to the total tonnage/estimated cost.
2. Specs for an item should be able to be packaged up and saved in the larger project (Grun) planned for the future.
