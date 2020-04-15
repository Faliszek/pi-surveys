open TW;
open Belt;

module Textarea = {
  [@react.component]
  let make = (~value, ~onChange, ~className=?) => {
    let className = className->Option.getWithDefault([]);

    <textarea
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
};

[@react.component]
let make = (~value, ~placeholder=?, ~onChange, ~className=?, ~htmlType="text") => {
  let className = className->Option.getWithDefault([]);

  <input
    type_=htmlType
    value
    ?placeholder
    onChange={e => e->ReactEvent.Synthetic.target##value->onChange}
    className={
      [
        BorderRadius(RoundedLg),
        BorderWidth(Border),
        BorderColor(BorderGray300),
        Padding(Px4),
        BoxShadow(ShadowMd),
        Height(H10),
      ]
      ->List.concat(className)
      ->make
    }
  />;
};