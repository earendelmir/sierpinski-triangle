triangle: clean triangle.c
	@echo "Generating executable \"triangle.out\""
	@gcc triangle.c -o triangle.out -lm
	@echo "Done"

clean:
	@echo "Cleaning up..."
	@rm -rf .points .vertices triangle.out
	@echo "Done"
