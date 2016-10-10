--Example
SELECT orders.orderID, customers.custID, firstname, familyname
FROM orders, lineitems, customers
WHERE lineitems.itemID = 's7'
AND orders.orderID = lineitems.orderID
AND orders.custID = customers.custID

SELECT state, Count( custID )
FROM customers
GROUP BY state;

--Q1
SELECT *
FROM customers
WHERE state = 'Arizona';

--Q2
SELECT sum(unitcost) AS total
FROM items, lineitems, orders
WHERE items.itemID = lineitems.itemID
AND lineitems.orderID = orders.orderID;

--Q3
SELECT COUNT(DISTINCT custID) AS ans
FROM customers
WHERE EXISTS (
    SELECT * 
    FROM lineitems, orders
    WHERE orders.orderID = lineitems.orderID
    AND customers.custID = orders.custID
    GROUP BY itemID, custID
    HAVING SUM(quantity) > 2
);

--Q4
SELECT state, COUNT(*) AS number
FROM customers
GROUP BY state
ORDER BY number DESC;

--Q5
SELECT custID, firstname, familyname, town, state
FROM customers
WHERE EXISTS (
    SELECT *
    FROM lineitems, orders
    WHERE orders.orderID = lineitems.orderID
    AND customers.custID = orders.custID
    GROUP BY custID
    HAVING COUNT(DISTINCT itemID) > 1
);

SELECT custID, itemID, COUNT(itemID)
FROM lineitems, orders
WHERE orders.orderID = lineitems.orderID
AND custID IN (
	SELECT custID
    FROM customers
    WHERE EXISTS (
        SELECT *
        FROM lineitems, orders
        WHERE orders.orderID = lineitems.orderID
        AND customers.custID = orders.custID
        GROUP BY custID
        HAVING COUNT(DISTINCT itemID) > 1
    )
)
GROUP BY custID, itemID;

--Q6
SELECT state, COUNT(DISTINCT custID) as number
FROM customers
WHERE EXISTS (
	SELECT *
	FROM items, lineitems, orders
	WHERE items.itemID = lineitems.itemID
	AND lineitems.orderID = orders.orderID
	AND orders.custID = customers.custID
	AND items.description = 'Umbrella'
)
GROUP BY state;

--Q7
SELECT lineitems.itemID, description, quantity
FROM lineitems, items
WHERE quantity = (
	SELECT MAX(quantity)
	FROM lineitems
	)
AND lineitems.itemID = items.itemID;

--Q8
