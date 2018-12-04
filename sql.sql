WITH CTE AS  
(SELECT product_id, o.customer_id, unit_price, ROW_NUMBER() OVER(PARTITION BY o.customer_id ORDER BY unit_price ASC) AS Row_num 
FROM order_details INNER JOIN Orders AS o
ON order_details.order_id = o.order_id)
SELECT product_id, customer_id, unit_price
FROM CTE
WHERE Row_num = 1;

SELECT COUNT(tmp.customer_id) as Row_num, tmp.customer_id
FROM(
	SELECT od.product_id, o.customer_id, od.unit_price
	FROM order_details od INNER JOIN orders o
	ON od.order_id = o.id
)tmp
GROUP BY tmp.customer_id
HAVING Row_num = 6;

SELECT tmp.customer_id, tmp.product_id, tmp.unit_price 
FROM (SELECT COUNT(o.customer_id) as Row_num, od.product_id, o.customer_id, od.unit_price 
    FROM order_details od, orders o 
    WHERE od.order_id = o.id
	GROUP BY o.customer_id) tmp
WHERE tmp.Row_num = 1;

SELECT tmp.customer_id, tmp.product_id, MIN(tmp.unit_price)min
FROM (SELECT od.product_id, o.customer_id, od.unit_price 
    FROM order_details od, orders o 
    WHERE od.order_id = o.id) tmp
GROUP BY tmp.customer_id
ORDER BY min ASC;