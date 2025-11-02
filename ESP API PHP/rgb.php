<!DOCTYPE html>
<html>
<form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">

  
    <label for="r">Red:</label>
    <input type="range" id="r" name="r" min="0" max="255" value="0" oninput="this.nextElementSibling.value = this.value">
    <output id="rOut">0</output>
    <p></p>
  <p>
    <label for="g">Green:</label>
    <input type="range" id="g" name="g" min="0" max="255" value="0" oninput="gOut.value = this.value">
    <output id="gOut">0</output>
  </p>
  <p>
    <label for="b">Blue:</label>
    <input type="range" id="b" name="b" min="0" max="255" value="0" oninput="bOut.value = this.value">
    <output id="bOut">0</output>
  </p>

  <input type="submit" value="Submit Values">
</form>
<p>Red: <div id="redtxt"></div></p>
<p>Green: <div id="greentxt"></div></p>
<p>Blue: <div id="bluetxt"></div></p>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $r = $_POST["r"] ?? 0;
    $g = $_POST["g"] ?? 0;
    $b = $_POST["b"] ?? 0;

    // Write to rgb.txt
    file_put_contents("rgb.txt", "$r,$g,$b");

    echo "<p>Saved values: R=$r, G=$g, B=$b</p>";
}
?>

<script>
    // poll rgb.txt
    async function pollRGB() {
    try {
        const res = await fetch('rgb.txt?nocache=' + Date.now());
        const text = await res.text();
        const parts = text.trim().split(',');
        if (parts.length === 3) {
        const [r, g, b] = parts.map(x => parseInt(x.trim(), 10));
        if (!isNaN(r) && !isNaN(g) && !isNaN(b)) {
            document.getElementById('redtxt').textContent = r;
            document.getElementById('greentxt').textContent = g;
            document.getElementById('bluetxt').textContent = b;
        }
        }
    } catch (err) {
        console.error('Error reading rgb.txt:', err);
    }
    }

    // Run every 3 seconds
    pollRGB();
    setInterval(pollRGB, 3000);
</script>
</html>