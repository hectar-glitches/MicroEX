Day 1: project setup + core models

Set up the repo and define the core types.

You want:
	•	Order
	•	Trade
	•	Side enum
	•	OrderType enum
	•	maybe a basic Event struct for future replay

Fields for Order:
	•	order_id
	•	symbol
	•	side
	•	type
	•	price
	•	quantity
	•	timestamp

Fields for Trade:
	•	buy_order_id
	•	sell_order_id
	•	price
	•	quantity
	•	timestamp

Also set up:
	•	build system, likely CMake
	•	folder structure
	•	a few sample input cases
	•	GitHub repo with a minimal README

Day 2: order book data structures

Implement the internal book.

At v1, keep it simple and correct.

You need:
	•	bid side sorted highest price first
	•	ask side sorted lowest price first
	•	FIFO within each price level

A clean conceptual model:
	•	map<price, deque<Order>> for asks
	•	map<price, deque<Order>, greater<>> for bids

You can optimize later.

Also add a function to print:
	•	best bid
	•	best ask
	•	current depth per price level

Day 3: matching logic for limit orders

This is the heart of the project.

Implement:
	•	incoming buy limit matches lowest asks while buy_price >= best_ask
	•	incoming sell limit matches highest bids while sell_price <= best_bid
	•	if quantity remains, rest it on the book
	•	record each trade
	•	maintain price-time priority

You must handle:
	•	full fills
	•	partial fills
	•	walking through multiple price levels

At the end of Day 3, you should be able to process a short sequence of limit orders correctly.

Day 4: CLI or file-driven input

Do not build a GUI.

Add one of these:
	•	simple CLI command parser, or
	•	read orders from a text/CSV file

Example commands:
	•	BUY LIMIT 100 10
	•	SELL LIMIT 101 5

Or use CSV:
	•	timestamp,order_id,side,type,price,qty

This makes the project runnable and demoable.

Day 5: correctness testing

This matters a lot.

Write small tests for:
	•	simple one-to-one match
	•	partial fill
	•	multiple orders at same price
	•	multiple price levels
	•	unmatched order resting on book
	•	price-time priority

Even if the tests are basic, they make the repo feel serious.

Day 6: trade log + pretty output

Make the engine pleasant to inspect.

Add:
	•	trade log output
	•	end-of-run order book snapshot
	•	maybe step-by-step event processing printout

A user should be able to run a sample file and immediately understand:
	•	what orders came in
	•	what matched
	•	what remains

Day 7: cleanup + README

This is important.

Write a README with:
	•	project description
	•	supported features in v1
	•	build instructions
	•	sample input
	•	sample output
	•	what’s coming next

Also add one architecture sketch:
	•	input → matching engine → order book → trade log