// Example
SELECT orders.orderID, customers.custID, firstname, familyname
FROM orders, lineitems, customers
WHERE lineitems.itemID = 's7'
AND orders.orderID = lineitems.orderID
AND orders.custID = customers.custID

SELECT state, Count( custID )
FROM customers
GROUP BY state
LIMIT 0 , 30

// Q1
SELECT *
FROM customers
WHERE state = 'Arizona'
LIMIT 0 , 30

// Q2
SELECT sum( unitcost ) AS total
FROM items, lineitems, orders
WHERE items.itemID = lineitems.itemID
AND lineitems.orderID = orders.orderID

// Q3
SELECT custID, itemID, sum(quantity) as sum
FROM lineitems, orders
WHERE orders.orderID = lineitems.orderID
group by itemID, custID
order by custID;

select count(distinct custID) as ans
from orders
where exists (
    SELECT * FROM lineitems, orders
    WHERE orders.orderID = lineitems.orderID
    having sum(quantity) > 2
    );
