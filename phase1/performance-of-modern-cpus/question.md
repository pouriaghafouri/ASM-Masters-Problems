
<div class="rtl">
</div>

<div>
  برنامه‌ای بنویسید که وضعیت یک آرایه داده‌شده را تحت عملیات مشخص‌شده بررسی کند. آرایه A = [a₁, a₂, a₃, ..., aₙ] داده می‌شود و شما باید q عملیات مشخص‌شده را بر روی آن انجام دهید.
</div>

<div class="section">عملیات:</div>
<div style="direction: rtl; font-size: 18px;">
  <p>
    1. <b>عملیات نوع اول:</b><br>
    به شما سه عدد <span style="font-family: 'Courier New', monospace;">l</span> و <span style="font-family: 'Courier New', monospace;">r</span> و <span style="font-family: 'Courier New', monospace;">x</span> داده می‌شود و شما باید عملیات زیر را انجام دهید:
    <span class="formula">aᵢ := (aᵢ + x) % 65536 برای l ≤ i ≤ r</span>
  </p>
  <p>
    2. <b>عملیات نوع دوم:</b><br>
    به شما سه عدد <span style="font-family: 'Courier New', monospace;">l</span> و <span style="font-family: 'Courier New', monospace;">r</span> و <span style="font-family: 'Courier New', monospace;">x</span> داده می‌شود و شما باید عملیات زیر را انجام دهید (منظور از ⊕، عمل bitwise xor است):
    <span class="formula">aᵢ := aᵢ ⊕ x برای l ≤ i ≤ r</span>
  </p>
  <p>
    3. <b>عملیات نوع سوم:</b><br>
    به شما دو عدد <span style="font-family: 'Courier New', monospace;">l</span> و <span style="font-family: 'Courier New', monospace;">r</span> داده می‌شود و باید مقدار زیر را محاسبه کنید:
    <span class="formula">min(aᵢ) برای l ≤ i ≤ r</span>
  </p>
</div>

<div class="section">هدف:</div>
<div style="direction: rtl; font-size: 18px;">
  با اینکه هر راه حل درستی پذیرفته می‌شود، هدف طراحی راه‌حلی است که پیچیدگی زمانی <span style="font-family: 'Courier New', monospace;">O(nq)</span> داشته باشد و به اندازه‌ای سریع باشد که در محدودیت زمانی بگنجد.
  پیشنهاد می‌شود که به <b> vector extension</b>های ®Intel نگاهی بیندازید.
</div>

<div class="section">ورودی:</div>
<div style="direction: rtl; font-size: 18px;">
  ورودی شامل چهار قسمت است:
  <ul>
    <li>عدد <span style="font-family: 'Courier New', monospace;">n</span>: طول آرایه A</li>
    <li>آرایه A شامل <span style="font-family: 'Courier New', monospace;">n</span> عدد</li>
    <li>عدد q: تعداد عملیات</li>
    <li>
      <span style="font-family: 'Courier New', monospace;">q</span> خط بعدی شامل توضیحات عملیات:
      <ul>
        <li>اگر عملیات از نوع اول باشد: خط ورودی شامل چهار عدد <span style="font-family: 'Courier New', monospace;"> x ,r ,l ,1 </span> است.</li>
        <li>اگر عملیات از نوع دوم باشد: خط ورودی شامل چهار عدد <span style="font-family: 'Courier New', monospace;">x ,r ,l ,2 </span> است.</li>
        <li>اگر عملیات از نوع سوم باشد: خط ورودی شامل سه عدد <span style="font-family: 'Courier New', monospace;"> r ,l ,3 </span> است.</li>
      </ul>
    </li>
  </ul>
</div>

<div class="section">خروجی:</div>
<div style="direction: rtl; font-size: 18px;">
  برای هر عملیات نوع سوم، مقدار محاسبه‌شده را در یک خط چاپ کنید.
</div>

<div class="section">محدودیت‌ها:</div>
<div style="text-align: center; font-size: 18px;">
  16 ≤ n ≤ 10<sup>5</sup><br>
  1 ≤ q ≤ 3 × 10<sup>5</sup><br>
  0 ≤ aᵢ, x ≤ 65535<br>
  1 ≤ l ≤ r ≤ n <br>
<div style="direction=rtl;">
طول بازه‌‌ی یک عملیات، یعنی r - l + 1 مضرب ۱۶ است </div>
</div>

---

### ورودی نمونه:
```plaintext
16
1 1 1 1 2 2 2 2 4 4 4 4 8 8 8 8
3
1 1 16 2
2 1 16 8
3 1 16
```

### خروجی نمونه:
```plaintext
2
```
