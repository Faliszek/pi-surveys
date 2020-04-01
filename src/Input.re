open TW;
open Belt;

[@react.component]
let make = (~value, ~onChange, ~className=?) => {
  let className = className->Option.getWithDefault([]);

  <input
    type_="text"
    value
    onChange={e => e->ReactEvent.Synthetic.target##value->onChange}
    className={
      [
        BorderRadius(RoundedLg),
        BorderWidth(Border),
        BorderColor(BorderGray300),
        Padding(Px4),
        Padding(Py1),
        Margin(M1),
        BoxShadow(ShadowMd),
        Height(H10),
      ]
      ->List.concat(className)
      ->make
    }
  />;
};