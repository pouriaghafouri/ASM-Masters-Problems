
<div class="rtl">

</div>

در این سوال n عدد ممیز شناور به شما داده می‌شود و شما باید برای هرکدام تابع erf در کتابخانه C را صدا بزنید.

### ورودی:
در خط اول ورودی عدد n که تعداد ورودی‌ها است به شما داده می‌شود. در n خط بعدی، در هر خط یک عدد Double Precision IEEE-754 به صورت مبنای 16 به شما داده می‌شود. دقت کنید که ورودی‌ها به صورت انکود شده به 16 رقم هگز می‌باشند.

### خروجی:
برای هر عدد Double Presicion، باید خروجی تابع erf را به ازای آن عدد به صورت مبنای 16 خروجی دهید. همچنین خروجی‌ها نیز به صورت انکود شده به 16 رقم هگز می‌باشند.

###  ورودی نمونه ۱:
```
2
3ff0000000000000
0000000000000000
```

### خروجی نمونه ۱:
```
3feaf767a741088b
0000000000000000
```

توضیحات: عدد اول در ورودی معادل با 1.0 و عدد اول در خروجی تقریبا برابر 0.842701 است. دقت کنید که مقدار دقیق خروجی وابسته پیاده سازی کتابخانه‌ی سی است و ممکن است تفاوت جزئی بین خروجی شما و خروجی نمونه باشد. هنگام داوری کد شما با همان کتابخانه‌ی داور قضاوت می‌شود.
