CREATE OR REPLACE VIEW statistics AS
	SELECT
		wp_statistics_pages.ID AS id,
		SUM(wp_statistics_pages.count) AS counter,
		wp_posts.post_title AS title
	FROM
		wp_statistics_pages
	INNER JOIN
		wp_posts ON wp_posts.ID = wp_statistics_pages.id
	WHERE
		wp_posts.post_title != '' AND wp_posts.post_title IS NOT NULL
	GROUP BY
		wp_statistics_pages.ID,
		wp_posts.post_title
	ORDER BY
		counter DESC
;
